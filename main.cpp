
#include <iostream>
#include <vector>

#include "./semaphore/ZybSemaphore.h"
#include <thread>

#include <sys/time.h>
#include <time.h>
#include <unistd.h>


using namespace std;

ZybSemaphore sem;
string fa_getSysTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    struct tm* pTime;
    pTime = localtime(&tv.tv_sec);

    char sTemp[30] = {0};
    snprintf(sTemp, sizeof(sTemp), "%04d%02d%02d%02d%02d%02d%03d%03d", pTime->tm_year+1900, \
            pTime->tm_mon+1, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec, \
            tv.tv_usec/1000,tv.tv_usec%1000);
    return (string)sTemp;
}

//线程处理函数f1
void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::cout << "Thread " << n << " executing  begin :"<< fa_getSysTime() << endl;
        sem.signal();
        std::cout << "Thread 1 executing finshed"<<endl;

    }
}
void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 2 _"<<i<<" executing now begin"<<endl;
        sem.wait();
        std::cout << "Thread 2 _"<<i<<" executing now "<<fa_getSysTime() << endl;
        ++n;
        if(i = 3){
            sem.cleanSignal();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

//for 
int main() {
    std::cout << "Hello, World!" << std::endl;

    int n = 0;
    std::thread t1;
    std::thread t2(f1,n+1);
    std::thread t3(f2,std::ref(n));
    t2.join();
    t3.join();

    //findMedianSortedArrays(sum1,sum2);
    return 0;
}
