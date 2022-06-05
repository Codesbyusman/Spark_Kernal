#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <sys/wait.h>
#include <iomanip>
#include <fstream>
#include <bits/stdc++.h>

#include <list>
#include <queue>

#include "CPU.h"

int totalWaitingTime;

using namespace std;

int timeStart;
int timeSpent;

pthread_mutex_t cpuLock;
pthread_mutex_t readyQueueLock;

pthread_t updateId;
pthread_t scheduleId;

// the global memory
list<CPU> kernalCPUs; // the cpus in kernal

// the five states
list<PCB> newState;        // the new state
queue<PCB> readyQueue;     // the ready queue
list<PCB> runningProcess;  // the running process --running state
list<PCB> terminatedState; // the terminated one
queue<PCB> blockedState;   // the i/o busy processes

int contextSwitchCount = 0;
int processCount = 0;
int poped = 0;

struct Scheduler
{

    list<CPU>::iterator cpuTraverse;
    time_t currentTime;

    void FCFS(const int cpuCount, string outputFile)
    {

        ofstream output;

        output.open(outputFile, ios::trunc | ios::out | ios::in);

        // the title printing
        cout << setw(6) << "Time " << setw(10) << "Ready" << setw(10) << "Running" << setw(10) << "waiting";

        output << setw(6) << "Time " << setw(10) << "Ready" << setw(10) << "Running" << setw(10) << "waiting";

        for (int i = 0; i < cpuCount; i++)
        {
            cout << setw(10) << "CPU " << i + 1;
            output << setw(10) << "CPU " << i + 1;
        }

        cout << setw(20) << "I/O Queue" << endl
             << endl;
        output << setw(20) << "I/O Queue" << endl
               << endl;

        timeStart = 0;

        while (poped < processCount)
        {

            // in start printing the data of queues
            // currentTime = time(NULL);

            // data printing
            cout << setw(6) << (timeStart) << setw(10) << readyQueue.size() << setw(10) << runningProcess.size() << setw(10) << blockedState.size();
            output << setw(6) << (timeStart) << setw(10) << readyQueue.size() << setw(10) << runningProcess.size() << setw(10) << blockedState.size();

            CPU cpuPrint;

            // checking for the cpus
            for (cpuTraverse = kernalCPUs.begin(); cpuTraverse != kernalCPUs.end(); ++cpuTraverse)
            {
                cpuPrint = *cpuTraverse;
                // cpuPrint = *cpuTraverse;
                if (cpuPrint.currentProcess != NULL)
                {
                    cout << setw(15) << cpuPrint.currentProcess->processName;
                    output << setw(15) << cpuPrint.currentProcess->processName;
                }
                else
                {
                    cout << setw(15) << "idle";
                    output << setw(15) << "idle";
                }
            }
            cout << setw(20) << "NULL" << endl;
            output << setw(20) << "NULL" << endl;

            CPU Cpu;

            // looking for the cpu
            while (!((runningProcess.size() < cpuCount) && freeCpu(cpuCount, Cpu)))
                ;

            if (!readyQueue.empty())
            {
                PCB process = readyQueue.front();
                readyQueue.pop();
                poped++;
                contextSwitch(Cpu, &process);

                timeStart += process.cpuTime;
            }
        }

        // data printing
        cout << setw(6) << (timeStart) << setw(10) << readyQueue.size() << setw(10) << runningProcess.size() << setw(10) << blockedState.size();
        output << setw(6) << (timeStart) << setw(10) << readyQueue.size() << setw(10) << runningProcess.size() << setw(10) << blockedState.size();

        CPU cpuPrint;

        // checking for the cpus
        for (cpuTraverse = kernalCPUs.begin(); cpuTraverse != kernalCPUs.end(); ++cpuTraverse)
        {
            cpuPrint = *cpuTraverse;
            // cpuPrint = *cpuTraverse;
            if (cpuPrint.currentProcess != NULL)
            {
                cout << setw(15) << cpuPrint.currentProcess->processName;
                output << setw(15) << cpuPrint.currentProcess->processName;
            }
            else
            {
                cout << setw(15) << "idle";
                output << setw(15) << "idle";
            }
        }
        cout << setw(20) << "NULL" << endl;
        output << setw(20) << "NULL" << endl;

        cout << "\n\t :::::::::::::::::::::::::::::::::::::::: \n"
             << endl;
        cout << "\n\t    # of context switching : " << contextSwitchCount << endl;
        cout << "\t    Total Execution Time : " << timeStart << endl;
        cout << "\t    Total waiting in ready state : " << totalWaitingTime << endl;
        cout << "\n\t :::::::::::::::::::::::::::::::::::::::: \n"
             << endl;

        // writing in to the file
        output << "\n\t :::::::::::::::::::::::::::::::::::::::: \n"
               << endl;
        output << "\n\t    # of context switching : " << contextSwitchCount << endl;
        output << "\t    Total Execution Time : " << timeStart << endl;
        output << "\t    Total waiting in ready state : " << totalWaitingTime << endl;
        output << "\n\t :::::::::::::::::::::::::::::::::::::::: \n"
               << endl;

        output.close();
    }

    void Piority(const int cpuCount, string outputFile)
    {
        ofstream output;

        output.open(outputFile, ios::trunc | ios::out | ios::in);

        // the title printing
        cout << setw(6) << "Time " << setw(10) << "Ready" << setw(10) << "Running" << setw(10) << "waiting";

        output << setw(6) << "Time " << setw(10) << "Ready" << setw(10) << "Running" << setw(10) << "waiting";

        for (int i = 0; i < cpuCount; i++)
        {
            cout << setw(10) << "CPU " << i + 1;
            output << setw(10) << "CPU " << i + 1;
        }

        cout << setw(20) << "I/O Queue" << endl
             << endl;
        output << setw(20) << "I/O Queue" << endl
               << endl;

        timeStart = 0;

        while (poped < processCount)
        {

            // in start printing the data of queues
            // currentTime = time(NULL);

            // data printing
            cout << setw(6) << (timeStart) << setw(10) << readyQueue.size() << setw(10) << runningProcess.size() << setw(10) << blockedState.size();
            output << setw(6) << (timeStart) << setw(10) << readyQueue.size() << setw(10) << runningProcess.size() << setw(10) << blockedState.size();

            CPU cpuPrint;

            // checking for the cpus
            for (cpuTraverse = kernalCPUs.begin(); cpuTraverse != kernalCPUs.end(); ++cpuTraverse)
            {
                cpuPrint = *cpuTraverse;
                // cpuPrint = *cpuTraverse;
                if (cpuPrint.currentProcess != NULL)
                {
                    cout << setw(15) << cpuPrint.currentProcess->processName;
                    output << setw(15) << cpuPrint.currentProcess->processName;
                }
                else
                {
                    cout << setw(15) << "idle";
                    output << setw(15) << "idle";
                }
            }
            cout << setw(20) << "NULL" << endl;
            output << setw(20) << "NULL" << endl;

            CPU Cpu;

            // looking for the cpu
            while (!((runningProcess.size() < cpuCount) && freeCpu(cpuCount, Cpu)))
                ;

            if (!readyQueue.empty())
            {
                sortMe(readyQueue);
                PCB process = readyQueue.front();
                readyQueue.pop();
                poped++;
                contextSwitch(Cpu, &process);
                timeStart += process.cpuTime;
            }
        }

        // data printing
        cout << setw(6) << (timeStart) << setw(10) << readyQueue.size() << setw(10) << runningProcess.size() << setw(10) << blockedState.size();
        output << setw(6) << (timeStart) << setw(10) << readyQueue.size() << setw(10) << runningProcess.size() << setw(10) << blockedState.size();

        CPU cpuPrint;

        // checking for the cpus
        for (cpuTraverse = kernalCPUs.begin(); cpuTraverse != kernalCPUs.end(); ++cpuTraverse)
        {
            cpuPrint = *cpuTraverse;
            // cpuPrint = *cpuTraverse;
            if (cpuPrint.currentProcess != NULL)
            {
                cout << setw(15) << cpuPrint.currentProcess->processName;
                output << setw(15) << cpuPrint.currentProcess->processName;
            }
            else
            {
                cout << setw(15) << "idle";
                output << setw(15) << "idle";
            }
        }
        cout << setw(20) << "NULL" << endl;
        output << setw(20) << "NULL" << endl;

        cout << "\n\t :::::::::::::::::::::::::::::::::::::::: \n"
             << endl;
        cout << "\n\t    # of context switching : " << contextSwitchCount << endl;
        cout << "\t    Total Execution Time : " << timeStart << endl;
        cout << "\t    Total waiting in ready state : " << totalWaitingTime << endl;
        cout << "\n\t :::::::::::::::::::::::::::::::::::::::: \n"
             << endl;

        // writing in to the file
        output << "\n\t :::::::::::::::::::::::::::::::::::::::: \n"
               << endl;
        output << "\n\t    # of context switching : " << contextSwitchCount << endl;
        output << "\t    Total Execution Time : " << timeStart << endl;
        output << "\t    Total waiting in ready state : " << totalWaitingTime << endl;
        output << "\n\t :::::::::::::::::::::::::::::::::::::::: \n"
               << endl;

        output.close();
    }

    void roundRobbin(const int cpuCount, string outputFile, int timeSlice)
    {
    }

    void terminate(PCB process)
    {
        process.state = "completed";
        process.completionTime = timeStart;

        totalWaitingTime += ((process.completionTime - process.arrivalTime) - process.cpuTime + process.inputOutputTime);

        list<PCB>::iterator iterate;
        PCB p;

        // checking for the cpus
        for (iterate = runningProcess.begin(); iterate != runningProcess.end(); ++iterate)
        {
            p = *iterate;
            if (p.pid == process.pid)
            {
                if (!runningProcess.empty())
                {
                    // cout << p.pid << endl;

                    runningProcess.pop_back();
                    terminatedState.push_back(process);
                    return;
                    // printLists(runningProcess);
                }
            }
        }
    }

    // prining of the lists
    void printLists(list<PCB> toPrint)
    {
        PCB iteration;
        list<PCB>::iterator pcbTraverse;

        // checking for the cpus
        for (pcbTraverse = toPrint.begin(); pcbTraverse != toPrint.end(); pcbTraverse++)
        {
            iteration = *pcbTraverse;
            iteration.printProcess();
        }
    }

    void contextSwitch(CPU &assignTothis, PCB *process)
    {

        if (process != NULL)
        {

            CPU iterate;
            // checking for the cpus
            for (cpuTraverse = kernalCPUs.begin(); cpuTraverse != kernalCPUs.end(); cpuTraverse++)
            {
                iterate = *cpuTraverse;

                if (assignTothis.id == iterate.id)
                {
                    assignTothis.currentProcess = process;
                    assignTothis.currentProcess->state = "running";
                    assignTothis.status = true;
                    contextSwitchCount++;
                    if (process->inputOutputTime > 0)
                    {
                        contextSwitchCount += process->inputOutputTime;
                    }

                    *cpuTraverse = assignTothis;

                    runningProcess.push_back(*process);
                }
            }
        }
    }

    // will look for the free cpu
    bool freeCpu(const int totalCpu, CPU &required)
    {

        if (!kernalCPUs.empty())
        {
            // checking for the cpus
            for (cpuTraverse = kernalCPUs.begin(); cpuTraverse != kernalCPUs.end(); ++cpuTraverse)
            {

                required = *cpuTraverse;
                // if cpu is free return this
                if (required.status)
                {
                    pthread_mutex_trylock(&cpuLock);

                    // as found thus make that cpu is occupied
                    required.status = false;
                    *cpuTraverse = required;

                    pthread_mutex_unlock(&cpuLock);
                    // returning
                    return true;
                }
            }
        }
        // returning
        return false;
    }

    bool freeTheCPU(CPU cpu)
    {
        CPU required;
        // checking for the cpus
        for (cpuTraverse = kernalCPUs.begin(); cpuTraverse != kernalCPUs.end(); ++cpuTraverse)
        {
            required = *cpuTraverse;
            // if cpu ids match free the cpu it's work is done
            if (required.id == cpu.id)
            {

                // as found thus make that cpu is occupied
                required.status = true;
                // required.currentProcess = NULL;
                *cpuTraverse = required;
                return true;
            }
        }

        return false;
    }

    // will find the last most index in the queue
    int findtheLeast(queue<PCB> &sortingThis, int index)
    {
        int min = -1;
        int min_val = sortingThis.front().pirority;
        int n = sortingThis.size();

        for (int i = 0; i < n; i++)
        {
            PCB currentIteration = sortingThis.front();
            sortingThis.pop(); // dequeue()

            if (i <= index && currentIteration.pirority <= min_val)
            {
                min = i;
                min_val = currentIteration.pirority;
            }
            sortingThis.push(currentIteration); //  enqueue()
        }
        return min;
    }

    // will insert inthat least index found
    void insertToleastFound(queue<PCB> &sortThis, int min_index)
    {
        PCB minPriorityProcess;
        int n = sortThis.size();
        for (int i = 0; i < n; i++)
        {
            // taking the front --- first eklement
            PCB iterate = sortThis.front();
            sortThis.pop();

            if (min_index != i)
            {
                sortThis.push(iterate);
            }
            else
            {
                minPriorityProcess = iterate;
            }
        }
        sortThis.push(minPriorityProcess);
    }

    // will sort according to priority
    void sortMe(queue<PCB> &process)
    {

        for (int i = 1; i <= process.size(); i++)
        {
            // for each time -- equal to size check the least one
            int min_index = findtheLeast(process, process.size() - i);
            insertToleastFound(process, min_index);
        }
    }
};
