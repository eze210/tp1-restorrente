//
// Created by fabrizio on 15/10/16.
//

#include <utils/Logger.h>
#include <domain/Order.h>
#include <data/Config.h>
#include <OrdersQueue.h>
#include <DishesQueue.h>
#include "Waiter.h"
Waiter::Waiter(uint32_t waiterID) : id(waiterID) {
}

void Waiter::addOrder(uint32_t tableID, OrderID order) {
    LOGGER << "Waiter " << getpid() << " waiting for the order" << logger::endl;

    OrdersQueue::getInstance().addNewOrder(order);
    LOGGER << "Waiter " << getpid() << " receiving the order " <<
    order << " from door, going to lobby" <<
    logger::endl;
    {
        /* NOT SYNC! just simulates time to take the clients
         * to lobby or to table */
        sleep(1);
    }
    LOGGER << "Waiter " << getpid() <<
    " waiting for clients in the door" << logger::endl;
}

OrderID Waiter::getDish(uint32_t tableID) {
    LOGGER << "Waiter " << id << " waiting for the order of table" <<
            tableID << "to be prepared" << logger::endl;

    OrderID order = DishesQueue::getInstance().getPreparedDish();
    LOGGER << "Waiter " << id << " received the dish" <<
            order << "from the kitchen." << logger::endl;
    LOGGER << "Waiter " << id << " serving the dish to table " <<
            tableID << logger::endl;
    return order;
}



void Waiter::setID(uint32_t waiterID) {
    id = waiterID;
}

uint32_t Waiter::getID() {
    return id;
}

Waiter::~Waiter() {
}
