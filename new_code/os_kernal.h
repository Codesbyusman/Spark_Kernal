#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <sys/wait.h>
#include <bits/stdc++.h>

// the link list
#include <list>
#include <queue>

using namespace std;

#include "scheduler.h"

// // the cpu structure
// struct CPU
// {
//     /* data */
//     pthread_t id;        // the id of thread
//     string name;         // name of the cpu thread
//     PCB *currentProcess; // the current running process
//     // PCB *previousProcess; // the previous excuted
//     bool status; // shows the status of if the status true the cpu is free

//     void displayCPU()
//     {
//         cout << "\n\n id : " << id << endl;
//         cout << "name : " << name << endl;
//         cout << "status : " << status << endl;
//         if (status)
//         {
//             cout << "Idle Process" << endl;
//         }
//         else
//         {
//             currentProcess->printProcess();
//         }

//         cout << endl;
//     }
// };

// for the thread making of the updating the ready queue
void *updateReadyQueue(void *args)
{
    // inifite loop and will update in contrast the ready queue
    while (1)
    {

        PCB theFirstinNew;
        string compare;
        // if time matches then going to the ready
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (!newState.empty())
                {
                    compare = to_string(i) + "." + to_string(j);
                    theFirstinNew = newState.front();
                    if (theFirstinNew.arrivalTime == stod(compare))
                    {
                        cout << i << "." << j << " " << theFirstinNew.arrivalTime << endl;
                        newState.pop_front();
                        // and pushing to the readyQueue
                        readyQueue.push(theFirstinNew);
                    }
                }
            }
        }
    }

    return NULL;
}

struct Os_kernal
{

    Scheduler kernalScheduler; // the scheduler

    // the iterator
    list<CPU>::iterator cpuTraverse;
    list<PCB>::iterator pcbTraverse;

    Os_kernal()
    {

        pthread_create(&updateId, NULL, updateReadyQueue, NULL);
    }

    // making the process
    void makeProcess(string info, const int id)
    {

        PCB P; // the process

        P.pid = id;         // the id
        P.ppid = getppid(); // the ppid
        P.state = "new";    // state of the prcess

        stringstream splitThestring(info); // will use the stream and will take one word from the given string
        string word;                       // the splited word

        splitThestring >> word; // extracting the name of the process

        // will make the process and will insert its pcb to new state
        P.processName = word;

        splitThestring >> word; // extracting th priority
        P.pirority = stoi(word);

        splitThestring >> word; // extracting the arrival
        P.arrivalTime = stod(word);

        splitThestring >> word; // extracting the type
        P.processType = word;

        splitThestring >> word; // extracting the cpu time

        // not specified
        if (word == P.processType)
        {

            P.cpuTime = (rand() % 10) + 1; // give some time between 10
            P.remaingExecution = P.cpuTime;
        }
        else
        {
            P.cpuTime = stod(word);
            P.remaingExecution = P.cpuTime;
        }

        splitThestring >> word; // extracting the i/o time

        // input output not specified
        if (word == P.processType)
        {
            // if cpu then no input output
            if (P.processType == "C")
            {
                P.inputOutputTime = -1; // no input output
            }
            else
            {
                P.inputOutputTime = (rand() % 10) + 1; // give some time between 5
            }
        }
        else
        {
            P.inputOutputTime = stod(word);
        }

        // the process is ready inserting in the new state -- its pcb
        newState.push_back(P);
    }

    // starting this
    void start(string fileName, void *(*functionPointer)(void *), pthread_t *cpuIds, int totalCPU)
    {

        // reading from file and setting the new state

        // reading from file
        ifstream inputFile;
        string line; // for reading

        inputFile.open(fileName); // opening the file

        if (inputFile.is_open())
        {
            // while not end of file
            getline(inputFile, line, '\n'); // taking the first line and ignoring as heading

            int i = 0;

            // while end of file is not encountered
            while (!inputFile.eof())
            {
                // while not end of file
                getline(inputFile, line, '\n');
                this->makeProcess(line, i); // making the process
                i++;
            }

            // if the file was open closing it
            inputFile.close();

            // till now the new queue made thus sorting the queue
            // newState.sort();

            CPU C;

            // now making the cpus
            for (int i = 0; i < totalCPU; i++)
            {

                // making the cpu
                C.name = "CPU - 0" + to_string(i + 1);
                C.id = i;
                C.status = true;
                C.currentProcess = NULL;

                kernalCPUs.push_back(C);

                // creating threads
                pthread_create(&cpuIds[i], NULL, functionPointer, &C);

                // sleep(1);
            }

            // check queues
            // cout << "::::::: Inready Qyeye ::::::::" << endl;
            // PCB q;
            // while (!readyQueue.empty())
            // {
            //     q = readyQueue.front();
            //     readyQueue.pop();

            //     q.printProcess();
            // }
        }
        else
        {
            cout << "\n\t :::::: Wrong Input File ::::::" << endl;
            return;
        }
    }

    // prining of the lists
    void printLists(list<PCB> toPrint)
    {
        PCB iteration;

        // checking for the cpus
        for (pcbTraverse = toPrint.begin(); pcbTraverse != toPrint.end(); ++pcbTraverse)
        {
            iteration = *pcbTraverse;
            iteration.printProcess();
        }
    }

    // will look for the free cpu
    CPU freeCpu(const int totalCpu)
    {
        // to return this
        CPU returnThis;

        // checking for the cpus
        for (cpuTraverse = kernalCPUs.begin(); cpuTraverse != kernalCPUs.end(); ++cpuTraverse)
        {
            returnThis = *cpuTraverse;
            // if cpu is free return this
            if (returnThis.status)
            {
                // returning
                return returnThis;
            }
        }

        // returning
        return returnThis;
    }

    void scheduleIt(const int totalCPU, char policy, int timeSlice)
    {

        cout << "scheduling the " << policy << " with time slice " << timeSlice << endl;

        cout << "y loo" << endl;

        if (policy == 'f')
        {

            kernalScheduler.FCFS(totalCPU);
        }
        else if (policy == 'r')
        {
        }
        else if (policy == 'p')
        {
        }
        else
        {
            cout << "bhaar ma jao" << endl;
        }
    }
};
