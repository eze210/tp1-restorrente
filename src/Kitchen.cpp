//
// Created by fabrizio on 15/10/16.
//

#include <zconf.h>
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
    mutex.unlock();

    mutex.lock();
        sleep(5);
        OrderID orderPrepared = orders.front();
        DishesQueue::getInstance().addPreparedDish(orderPrepared);
    mutex.unlock();
}
