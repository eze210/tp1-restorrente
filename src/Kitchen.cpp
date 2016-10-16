//
// Created by fabrizio on 15/10/16.
//

#include <zconf.h>
#include <utils/Logger.h>
#include "Kitchen.h"
#include "OrdersQueue.h"
#include "DishesQueue.h"

Kitchen::Kitchen() : mutex("kitchen.mutex") {
}

Kitchen::~Kitchen() { }

int Kitchen::run() {
    prepareOrder(OrdersQueue::getInstance().getOrder());
    return 0;
}

void Kitchen::prepareOrder(OrderID order) {
    mutex.lock();
        orders.push_back(order);
        LOGGER << "Kitchen received order " << order << logger::endl;
    mutex.unlock();

    mutex.lock();
        LOGGER << "Kitchen preparing order " << order << logger::endl;
        sleep(5);
        OrderID orderPrepared = orders.front();
        LOGGER << "Kitchen, order " << order << " prepared, sending to waiter" << logger::endl;
        DishesQueue::getInstance().addPreparedDish(orderPrepared);
    mutex.unlock();
}
