/*
    Muhammad usman shahid 20i-1797
    Ghulam Murtaza 20i-0957
 */

#include "process.h"

// the cpu structure
struct CPU
{
    /* data */
    pthread_t id;        // the id of thread
    string name;         // name of the cpu thread
    PCB *currentProcess; // the current running process
    // PCB *previousProcess; // the previous excuted
    bool status; // shows the status of if the status true the cpu is free

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
            currentProcess->printProcess();
        }

        cout << endl;
    }
};