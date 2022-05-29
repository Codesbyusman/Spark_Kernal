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
    int inputFile;          // to hold the input file discriptor
    int outputFile;         // to hold the input file discriptor
    double arrivalTime;     // the arrival time
    double completionTime;  // the completeion time
    string processName;     // the name
    double cpuTime;         // the cpu time
    double inputOutputTime; // the i/o time
};

class Process
{
public:
    PCB myPCB;

public:
    // Process(PCB P); // constructor
    // ~Process();     // destructor
};
