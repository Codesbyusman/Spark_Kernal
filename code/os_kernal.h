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

using namespace std;

// the cpu structure
struct CPU
{
    /* data */
    pthread_t id;           // the id of thread
    string name;            // name of the cpu thread
    Process currentProcess; // the current running process
};

class Os_kernal
{
private:
    list<Process> processes;   // the processes of kernal
    list<CPU> kernalCPUs;      // the cpus in kernal
    Scheduler kernalScheduler; // the scheduler

    // the five states

    list<PCB> readyQueue;      // the ready queue
    list<PCB> newState;        // the new state
    list<PCB> terminatedState; // the terminated one
    PCB runningProcess;        // the running process --running state
    list<PCB> blockedState;    // the i/o busy processes

public:
    Os_kernal();

    void *OSCPU(void *cpu); // the thread CPU

    void makeProcess(string info)
    {
        Process P; // the process

        stringstream splitThestring(info); // will use the stream and will take one word from the given string
        string word;                       // the splted word

        splitThestring >> word; // extracting the name of the process

        // will make the process and will insert its pcb to new state
        P.myPCB.processName = word;

        cout << endl;
    }

    bool processToreadyQueue(PCB);
    bool processTonewState(PCB);
    bool setRunninProcess(PCB);
    bool processTotermination(PCB);
    bool processTobloackage(PCB);

    ~Os_kernal();
};
