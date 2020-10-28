//
// Created by zhangyf on 2020-10-28.
//

#include "ZybSemaphore.h"


ZybSemaphore::ZybSemaphore(int value):count(value),wakeups(0) {

}

void ZybSemaphore::wait(){
    std::unique_lock<std::mutex> lock{mutex};
    if (--count<0) { // count is not enough ?
        condition.wait(lock, [&]()->bool{ return wakeups>0;}); // suspend and wait ...
        --wakeups;  // ok, me wakeup !
    }
}

void ZybSemaphore::signal(){
    std::lock_guard<std::mutex> lock{mutex};
    if(++count<=0) { // have some thread suspended ?
        ++wakeups;
        condition.notify_one(); // notify one !
    }
}
void ZybSemaphore::cleanSignal(){
    std::lock_guard<std::mutex> lock{mutex};
    count = 0;
}