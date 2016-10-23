#ifndef RESTORRENTE_WAITERSQUEUE_H
#define RESTORRENTE_WAITERSQUEUE_H

#include "Semaphore.h"

class WaitersQueue {
private:
    Semaphore waiterSemaphore;

public:
    WaitersQueue();
    void freeWaiter();
    void getWaiter();
    ~WaitersQueue();
};

#endif
