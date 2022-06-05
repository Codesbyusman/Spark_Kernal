#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <sys/wait.h>
#include <iomanip>

#include <list>
#include <queue>

#include "CPU.h"

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

    void FCFS(const int cpuCount)
    {

        // the title printing
        cout << setw(6) << "Time " << setw(10) << "Ready" << setw(10) << "Running" << setw(10) << "waiting";

        for (int i = 0; i < cpuCount; i++)
        {
            cout << setw(10) << "CPU " << i + 1;
        }

        cout << setw(20) << "I/O Queue" << endl
             << endl;

        timeStart = 0;

        while (poped < processCount)
        {

            // in start printing the data of queues
            // currentTime = time(NULL);

            // data printing
            cout << setw(6) << (timeStart) << setw(10) << readyQueue.size() << setw(10) << runningProcess.size() << setw(10) << blockedState.size();

            // CPU cpuPrint;

            for (int i = 0; i < cpuCount; i++)
            {
                cout << setw(10) << "CPU " << i + 1;
            }
            // // checking for the cpus
            // for (cpuTraverse = kernalCPUs.begin(); cpuTraverse != kernalCPUs.end(); ++cpuTraverse)
            // {
            //     // cpuPrint = *cpuTraverse;
            //     // cout << setw(10) << cpuPrint.currentProcess->processName;
            // }
            cout << setw(20) << "NULL" << endl;

            CPU Cpu;

            // looking for the cpu
            while (!freeCpu(cpuCount, Cpu))
                ;
            if (!readyQueue.empty())
            {

                PCB process = readyQueue.front();
                readyQueue.pop();
                poped++;
                contextSwitch(Cpu, &process);
                terminate();
                timeStart += process.cpuTime;
            }
                }

        // data printing
        cout << setw(6) << (timeStart) << setw(10) << readyQueue.size() << setw(10) << runningProcess.size() << setw(10) << blockedState.size();

        // CPU cpuPrint;

        for (int i = 0; i < cpuCount; i++)
        {
            cout << setw(10) << "CPU " << i + 1;
        }
        // // checking for the cpus
        // for (cpuTraverse = kernalCPUs.begin(); cpuTraverse != kernalCPUs.end(); ++cpuTraverse)
        // {
        //     // cpuPrint = *cpuTraverse;
        //     // cout << setw(10) << cpuPrint.currentProcess->processName;
        // }
        cout << setw(20) << "NULL" << endl;
    }

    void terminate()
    {
    }

    void contextSwitch(CPU &assignTothis, PCB *process)
    {

        if (process != NULL)
        {

            assignTothis.currentProcess = process;
            assignTothis.currentProcess->state = "running";
            assignTothis.status = true;
            contextSwitchCount++;

            runningProcess.push_back(*process);
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
                required.currentProcess = NULL;
                *cpuTraverse = required;

                return true;
            }
        }

        return false;
    }
};
