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
    pid_t pid;              // process id
    pid_t ppid;             // parent process id
    // string inputFile;       // to hold the input file discriptor
    // string outputFile;      // to hold the input file discriptor
    double arrivalTime;     // the arrival time
    double completionTime;  // the completeion time
    string processName;     // the name
    double cpuTime;         // the cpu time
    double inputOutputTime; // the i/o time
    string processType;     // see cpu or i/o
    int pirority;        // the prirority
};

class Process
{
public:
    PCB myPCB;

public:
    // Process(PCB P); // constructor
    // ~Process();     // destructor

    void printProcess()
    {
        cout << "\n \n Pid : " << myPCB.pid << endl;
        cout << "PPid : " << myPCB.ppid << endl;
        cout << "name : " << myPCB.processName << endl;
        cout << "type : " << myPCB.processType << endl;
        cout << "cpu time : " << myPCB.cpuTime << endl;
        cout << "input time : " << myPCB.inputOutputTime << endl
             << endl;
    }
};
