#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <sys/wait.h>

using namespace std;

// the cpu structure
struct CPU
{
    /* data */
};

class Os_kernal
{
private:
    /* data */
public:
    Os_kernal(/* args */);
    // the thread CPU
    void *osCpu(void *cpu);
    ~Os_kernal();
};
