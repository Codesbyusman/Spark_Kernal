#include "os_kernal.h"

using namespace std;

int main(int argc, char *argv[])
{

    // main thread is the controller thread
    // creating other on specified
    if (argc > 1)
    {
    }
    else
    {
        cout << "\n\t\t ::::::::: Please Specify the Parameters ::::::::\n"
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

    return 0;
}

Os_kernal::Os_kernal(/* args */)
{
}

Os_kernal::~Os_kernal()
{
}

void *Os_kernal::osCpu(void *cpu)
{
}