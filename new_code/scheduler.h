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

int contextSwitchCount = 0;

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

            CPU Cpu;
            // looking for the cpu
            while (!freeCpu(cpuCount, Cpu))
                ;
            if (!readyQueue.empty())
            {
                PCB process = readyQueue.front();
                readyQueue.pop();
                contextSwitch(Cpu, &process);
            }
            else
            {
                cout << "idle" << endl;
            }
        }
    }

    void contextSwitch(CPU &assignTothis, PCB *process)
    {

        if (process != NULL)
        {
            cout << "\n context switch " << endl;
            assignTothis.currentProcess = process;
            assignTothis.currentProcess->state = "running";
            assignTothis.status = true;
            contextSwitchCount++;
        }
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
                // as found thus make that cpu is occupied
                required.status = false;
                *cpuTraverse = required;
                // returning
                return true;
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
