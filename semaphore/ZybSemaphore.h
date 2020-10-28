//
// Created by zhangyf on 2020-10-28.
//

#ifndef ANDROID_PRJ_ZYB_H
#define ANDROID_PRJ_ZYB_H

#include <mutex>
#include <condition_variable>


class ZybSemaphore {
public:
    ZybSemaphore(int value =0);
    void wait();
    void signal();
    void cleanSignal();

private:
    int count;
    int wakeups;
    std::mutex mutex;
    std::condition_variable condition;
};


#endif //ANDROID_PRJ_ZYB_H
