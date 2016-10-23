#include "WaitersQueue.h"
#include "Config.h"
#include "Logger.h"

#include <string>
#include <sys/wait.h>

/** Name to represent the semaphore in the file system. */
const static std::string waiterSemName("waiters.semaphore");

WaitersQueue::WaitersQueue() :
waiterSemaphore(waiterSemName, Config::getWaitersCount()) {
	LOGGER << "Creating waiters queue" << logger::endl;
}

void WaitersQueue::freeWaiter() {
    waiterSemaphore.v();
}

void WaitersQueue::getWaiter() {
    waiterSemaphore.p();
}

WaitersQueue::~WaitersQueue() {
    waiterSemaphore.erase();
}
