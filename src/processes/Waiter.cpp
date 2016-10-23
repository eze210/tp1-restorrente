#include "Waiter.h"

#include "Logger.h"
#include "Order.h"
#include "Config.h"
#include "Kitchen.h"
#include "WaitersQueue.h"
#include "CashRegister.h"

Waiter::Waiter(Kitchen& theKitchen, WaitersQueue &queue) : kitchen(theKitchen), queue(queue) {
	queue.getWaiter();
}

unsigned int Waiter::addOrder(uint32_t tableID, OrderID order) {
    LOGGER << "Waiter receiving the order " <<
    order << " from clients " << tableID << logger::endl;

    int cost = Config::getAvailableFoods().at(order).getCost();

    kitchen.prepareOrder(order, queue);

    LOGGER << "Waiter sent order " <<
    order << " to kitchen" << logger::endl;

	CashRegister::getInstance().addPaymentPromise(cost);
	return cost;
}

Waiter::~Waiter() {
	queue.freeWaiter();
}
