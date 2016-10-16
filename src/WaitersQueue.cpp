//
// Created by fabrizio on 16/10/16.
//

#include <data/Config.h>
#include <utils/Fifos/FifoWrite.h>
#include <utils/Fifos/FifoRead.h>
#include "WaitersQueue.h"
#include <string>
#include <utils/Logger.h>

/** Name to represent the fifo in the file system. */
const static std::string waiterFifoName("waiter.fifo");

/** Name to represent the semaphore in the file system. */
const static std::string waiterSemName("waiter.semaphore");


WaitersQueue::WaitersQueue() : waiterFifo(waiterFifoName),
                               waiterSemaphore(waiterSemName,
                               Config::getReceptionistsCount()) {
    pid_t pid = fork();
    if (pid == 0) {
        for (uint32_t i = 0; i < Config::getWaitersCount(); i++) {
            LOGGER << "Adding waiter " << i << logger::endl;
            this->addWaiter(i);
        }
    }
}

WaitersQueue::~WaitersQueue() {
    waiterSemaphore.erase();
    waiterFifo.release();
}

void WaitersQueue::addWaiter(uint32_t WaiterID) {
    /* fifo instance that only exists if the process uses this method */
    static FifoWrite waiterFifo(waiterFifoName);
    /* puts the id in the fifo */
    waiterSemaphore.v();
    waiterFifo.write(static_cast<const void *>(&WaiterID), sizeof WaiterID);
}

uint32_t WaitersQueue::getWaiter() {
    /* fifo instance that only exists if the process uses this method */
    static FifoRead WaiterFifo(waiterFifoName);
    /* blocks until an Waiter id is ready to be read */
    uint32_t WaiterID;
    waiterSemaphore.p();
    WaiterFifo.read(static_cast<void *>(&WaiterID), sizeof WaiterID);
    return WaiterID;
}
