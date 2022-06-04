#include "os_kernal.h"

// the link list and queues
#include <list>
#include <queue>

// the kernal oject
Os_kernal Spark_Kernal;

pthread_t *cpuId;

using namespace std;

// prototypes for the threads function
void *cpuProcessors(void *);

int main(int argc, char *argv[])
{
    int cpuCount = 0;

    // main thread is the controller thread
    // creating other on specified
    if (argc > 1)
    {
        // now the cpu creation
        if (argc >= 3)
        {
            cpuCount = stoi(argv[2]);        // counting cpu
            cpuId = new pthread_t[cpuCount]; // the array to hold the ids

            if (!(cpuCount != 1 && cpuCount != 2 && cpuCount != 4))
            {
                // starting the kernal
                Spark_Kernal.start(argv[1], &cpuProcessors, cpuId, cpuCount);

                // the scdeuling process
                Spark_Kernal.scheduleIt(&cpuProcessors, cpuCount);
            }
            else
            {
                cout << "\n\t :::::: Wrong CPU specified ::::::" << endl;
                return 0;
            }
        }
        else
        {
            goto error;
        }
    }
    else
    {

    error:
        cout << "\n\t\t ::::: Please Specify the Parameters Correctly ::::\n"
             << endl;
        cout << "\n <objectFile> <inputFile> <#of cpu> <schedulingPolicy> <timeSlice> <outputFile>\n"
             << endl;
        cout << "\t\t ::::::::: Where Scheduling Plicy as follow :::::::: \n"
             << endl;
        cout << "\t\t f for first come first serve"
             << endl;
        cout << "\t\t r for round robbin  and timeslice for it only "
             << endl;
        cout << "\t\t p for the pirority based scheduling \n"
             << endl;
    }

    // waiting for the threads
    for (int i = 0; i < cpuCount; i++)
    {
        pthread_join(cpuId[i], NULL);
    }

    // pthread_join(updateId, NULL);

    return 0;
}

// prototypes for the threads function
void *cpuProcessors(void *args)
{

    CPU *theCpu = (CPU *)args;
    theCpu->displayCPU();
}
