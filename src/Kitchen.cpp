//
// Created by fabrizio on 15/10/16.
//

#include <zconf.h>
#include <utils/Logger.h>
#include "Kitchen.h"
#include "OrdersQueue.h"
#include "DishesQueue.h"

/*
Kitchen::Kitchen() : mutex(LockFile("Kitchen.cpp")) {
}
*/
Kitchen::Kitchen(LockFile &lock) : mutex(lock) {
}

Kitchen::~Kitchen() { }

int Kitchen::run() {
    OrderID orderID = OrdersQueue::getInstance().getOrder();
    while (orderID >= 0) {
        prepareOrder(orderID);
        orderID = OrdersQueue::getInstance().getOrder();
    }
    return 0;
}

void Kitchen::prepareOrder(OrderID order) {
    mutex.tomarLock();
        orders.push_back(order);
        LOGGER << "Kitchen received order " << order << logger::endl;
    mutex.liberarLock();
}

OrderID Kitchen::getPreparedOrder() {
    mutex.tomarLock();
        OrderID orderPrepared = orders.front();
        LOGGER << "Kitchen preparing order " << orderPrepared << logger::endl;
        sleep(5);
        LOGGER << "Kitchen, order " << orderPrepared << " prepared, sending to waiter" << logger::endl;
        //DishesQueue::getInstance().addPreparedDish(orderPrepared);
    mutex.liberarLock();
    return orderPrepared;
}
