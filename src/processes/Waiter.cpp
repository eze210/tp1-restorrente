//
// Created by fabrizio on 15/10/16.
//

#include <utils/Logger.h>
#include <domain/Order.h>
#include <data/Config.h>
#include <OrdersQueue.h>
#include <DishesQueue.h>
#include <Kitchen.h>
#include "Waiter.h"
Waiter::Waiter(uint32_t waiterID, Kitchen& theKitchen) : id(waiterID), kitchen(theKitchen) {
}

void Waiter::addOrder(uint32_t tableID, OrderID order) {
    LOGGER << "Waiter " << id << " receiving the order " <<
    order << " from clients " << tableID << logger::endl;

    kitchen.prepareOrder(order);
    //OrdersQueue::getInstance().addNewOrder(order);
    LOGGER << "Waiter " << id << " sent order " <<
    order << " to kitchen" << logger::endl;
}

OrderID Waiter::getDish(uint32_t tableID) {
    LOGGER << "Waiter " << id << " waiting for the order of clients " <<
            tableID << " to be prepared " << logger::endl;

    //OrderID order = DishesQueue::getInstance().getPreparedDish();
    OrderID order = kitchen.getPreparedOrder();
    LOGGER << "Waiter " << id << " received the dish " <<
            order << " from the kitchen." << logger::endl;
    LOGGER << "Waiter " << id << " serving the dish to clients " <<
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
