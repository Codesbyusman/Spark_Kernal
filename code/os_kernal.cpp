#include "os_kernal.h"
#include <string.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{

     // main thread is the controller thread
     // creating other on specified
     if (argc > 1)
     {
          // now the cpu creation
          int cpuCount = stoi(argv[2]);

          if (!(cpuCount != 1 && cpuCount != 2 && cpuCount != 4))
          {
               Os_kernal Spark_Kernal;
               ifstream inputFile;
               string line; // for reading

               inputFile.open(argv[1]); // opening the file

               if (inputFile.is_open())
               {
                    // while not end of file
                    getline(inputFile, line, '\n'); // taking the first line and ignoring as heading

                    // while end of file is not encountered
                    while (!inputFile.eof())
                    {
                         // while not end of file
                         getline(inputFile, line, '\n');
                         cout << line << endl;
                         Spark_Kernal.makeProcess(line); // making the process
                    }

                    // if the file was open closing it
                    inputFile.close();

                    // CPU *cpu[3];

                    // file has been read successfully creating the threads
                    for (int i = 0; i < cpuCount; i++)
                    {
                         // pthread_create(&cpu[i].id, NULL, Spark_Kernal.OSCPU, (void *)cpu[i]);
                    }
               }
               else
               {
                    cout << "\n\t :::::: Wrong Input File ::::::" << endl;
                    return 0;
               }
          }
          else
          {
               cout << "\n\t :::::: Wrong CPU specified ::::::" << endl;
               return 0;
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

     return 0;
}

Os_kernal::Os_kernal()
{
}

Os_kernal::~Os_kernal()
{
}

void *Os_kernal::OSCPU(void *cpu)
{
}