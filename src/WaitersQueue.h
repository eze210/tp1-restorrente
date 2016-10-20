//
// Created by fabrizio on 16/10/16.
//

#ifndef RESTORRENTE_WAITERSQUEUE_H
#define RESTORRENTE_WAITERSQUEUE_H


#include <utils/Semaphore.h>
#include <utils/Fifos/Fifo.h>

class WaitersQueue {
private:
    Fifo waiterFifo;
    Semaphore waiterSemaphore;
    pid_t pid;
public:
    WaitersQueue();
    ~WaitersQueue();
    void addWaiter(uint32_t orderID);
    uint32_t getWaiter();
};


#endif //RESTORRENTE_WAITERSQUEUE_H
