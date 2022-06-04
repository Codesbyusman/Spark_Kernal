#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <sys/wait.h>

#include <list>
#include <queue>

#include "CPU.h"

using namespace std;

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

struct Scheduler
{
    // Scheduler(/* args */);
    // void idle();
    // void yeild();
    // void terminate();
    // void preempt();
    // void wakeUp();
    // ~Scheduler();

    list<CPU>::iterator cpuTraverse;

    void FCFS(const int cpuCount)
    {

        while (1)
        {
            if (!readyQueue.empty())
            {
                CPU Cpu;
                // looking for the cpu
                while (!freeCpu(cpuCount, Cpu))
                    ;

                // changing status in the array

                PCB process = readyQueue.front();
                readyQueue.pop();

                cout << "llll" << endl;
                //     //     ;

                contextSwitch(Cpu, &process);
            }
        }
    }

    void contextSwitch(CPU &assignTothis, PCB *process)
    {

        cout << "\n context switch " << endl;
        assignTothis.currentProcess = process;
        assignTothis.status = false;
        cout << "name" << assignTothis.name << endl;
        assignTothis.currentProcess->printProcess();
    }

    // will look for the free cpu
    bool freeCpu(const int totalCpu, CPU &required)
    {

        // checking for the cpus
        for (cpuTraverse = kernalCPUs.begin(); cpuTraverse != kernalCPUs.end(); ++cpuTraverse)
        {
            required = *cpuTraverse;
            // if cpu is free return this
            if (required.status)
            {

                // returning
                return true;
            }
        }

        // returning
        return false;
    }
};
