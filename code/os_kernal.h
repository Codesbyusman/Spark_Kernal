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

        splitThestring >> word; // extracting th priority
        cout << "kkk" << word << "KKK" << endl;
        P.myPCB.pirority = stoi(word);

        splitThestring >> word; // extracting the arrival
        cout << "kkk" << word << "KKK" << endl;
        P.myPCB.arrivalTime = stod(word);

        splitThestring >> word; // extracting the type
        P.myPCB.processType = word;

        splitThestring >> word; // extracting the cpu time
        cout << "kkk" << word << "KKK" << endl;

        // not specified
        if (word == P.myPCB.processType)
        {

            P.myPCB.cpuTime = (rand() % 10) + 1; // give some time between 10
        }
        else
        {
            P.myPCB.cpuTime = stod(word);
        }

        splitThestring >> word; // extracting the i/o time
        cout << "kkk" << word << "KKK" << endl;

        // input output not specified
        if (word == P.myPCB.processType)
        {
            // if cpu then no input output
            if (P.myPCB.processType == "C")
            {
                P.myPCB.inputOutputTime = -1; // no input output
            }
            else
            {
                P.myPCB.inputOutputTime = (rand() % 10) + 1; // give some time between 5
            }
        }
        else
        {
            P.myPCB.inputOutputTime = stod(word);
        }

        // the process list
        processes.push_back(P);

        // the process is ready inserting in the new state -- its pcb
        newState.push_back(P.myPCB);

        P.printProcess();
    }

    bool processToreadyQueue(PCB);
    bool processTonewState(PCB);
    bool setRunninProcess(PCB);
    bool processTotermination(PCB);
    bool processTobloackage(PCB);

    ~Os_kernal();
};
