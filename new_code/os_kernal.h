#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <sys/wait.h>
#include <bits/stdc++.h>

#include "process.h"
#include "scheduler.h"

// the link list
#include <list>
#include <queue>

using namespace std;

// the cpu structure
struct CPU
{
    /* data */
    pthread_t id;       // the id of thread
    string name;        // name of the cpu thread
    PCB currentProcess; // the current running process
    bool status;        // shows the status of if the status true the cpu is free

    void displayCPU()
    {
        cout << "\n\n id : " << id << endl;
        cout << "name : " << name << endl;
        cout << "status : " << status << endl;
        if (status)
        {
            cout << "Idle Process" << endl;
        }
        else
        {
            currentProcess.printProcess();
        }

        cout << endl;
    }
};

struct Os_kernal
{

    list<CPU> kernalCPUs;      // the cpus in kernal
    Scheduler kernalScheduler; // the scheduler

    // the iterator
    list<CPU>::iterator arrayTraverse;

    // the five states

    list<PCB> newState;        // the new state
    queue<PCB> readyQueue;     // the ready queue
    list<PCB> runningProcess;  // the running process --running state
    list<PCB> terminatedState; // the terminated one
    queue<PCB> blockedState;   // the i/o busy processes

    // making the process
    void makeProcess(string info)
    {

        PCB P; // the process

        stringstream splitThestring(info); // will use the stream and will take one word from the given string
        string word;                       // the splted word

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

            // while end of file is not encountered
            while (!inputFile.eof())
            {
                // while not end of file
                getline(inputFile, line, '\n');
                this->makeProcess(line); // making the process
            }

            // if the file was open closing it
            inputFile.close();

            // now making the cpus
            for (int i = 0; i < totalCPU; i++)
            {
                CPU C;

                // making the cpu
                C.name = "CPU - 0" + to_string(i + 1);
                C.id = i;
                C.status = true;

                kernalCPUs.push_back(C);

                // creating threads
                pthread_create(&cpuIds[i], NULL, functionPointer, &C);

                sleep(1);
            }
        }
        else
        {
            cout << "\n\t :::::: Wrong Input File ::::::" << endl;
            return;
        }
    }

    // will look for the free cpu
    CPU freeCpu(const int totalCpu)
    {
        // to return this
        CPU returnThis;

        // checking for the cpus
        for (arrayTraverse = kernalCPUs.begin(); arrayTraverse != kernalCPUs.end(); ++arrayTraverse)
        {
            returnThis = *arrayTraverse;
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

    void scheduleIt(void *(*functionPointer)(void *), int totalCPU)
    {
    }
};
