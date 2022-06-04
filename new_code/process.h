
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <sys/wait.h>

using namespace std;

// the PCB structure that the kernal will hold
struct PCB
{
    /* data */
    pid_t pid;               // process id
    pid_t ppid;              // parent process id
    double arrivalTime;      // the arrival time
    double completionTime;   // the completeion time
    string processName;      // the name
    double cpuTime;          // the cpu time
    double remaingExecution; // the remaing time
    double inputOutputTime;  // the i/o time
    string processType;      // see cpu or i/o
    int pirority;            // the prirority
    string state;            // will tell procees in which state
    void printProcess()
    {
        cout << "\n\t ::::: Details of the Process :::::\n"
             << endl;

        cout << "\nPid  : " << pid << endl;
        cout << "PPid : " << ppid << endl;
        cout << "Name : " << processName << endl;
        cout << "Type : " << processType << endl;
        cout << "Cpu   time : " << cpuTime << endl;
        cout << "Input time : " << inputOutputTime << endl;
        cout << "Arrival time : " << arrivalTime << endl;
        cout << "Priority : " << pirority << endl;
    }
};
