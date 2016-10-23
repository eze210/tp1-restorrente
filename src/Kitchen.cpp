#include "Logger.h"
#include "Kitchen.h"

Kitchen::Kitchen() : mutex("kitchen.mutex") {
}

void Kitchen::prepareOrder(OrderID order, WaitersQueue &waitersQueue) {
	LOGGER << "Waiter lets a order " << order <<
			" in the kitchen and goes to the queue" << logger::endl;
	waitersQueue.freeWaiter();

	mutex.lock();
	LOGGER << "Kitchen is preparing a order " << order << logger::endl;
	sleep(5);
	mutex.unlock();

	waitersQueue.getWaiter();
	LOGGER << "A waiter takes a order " << order <<
			" from the kitchen" << logger::endl;
}

Kitchen::~Kitchen() {
	mutex.release();
}
