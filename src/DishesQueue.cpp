//
// Created by fabrizio on 16/10/16.
//

#include <string>
#include <domain/Order.h>
#include <utils/Fifos/FifoWrite.h>
#include <utils/Fifos/FifoRead.h>
#include "DishesQueue.h"
/** Name to represent the fifo in the file system. */
const static std::string orderFifoName("dishes.fifo");

DishesQueue& DishesQueue::getInstance() {
    static DishesQueue instance;
    return instance;
}

DishesQueue::DishesQueue() : dishesFifo(orderFifoName) {}

DishesQueue::~DishesQueue() {}

void DishesQueue::addPreparedDish(OrderID orderID) {
    /* fifo instance that only exists if the process uses this method */
    static FifoWrite dishesFifo(orderFifoName);
    /* puts the id in the fifo */
    dishesFifo.write(static_cast<const void *>(&orderID), sizeof orderID);
}

OrderID DishesQueue::getPreparedDish() {
    /* fifo instance that only exists if the process uses this method */
    static FifoRead dishesFifo(orderFifoName);
    /* blocks until an order id is ready to be read */
    OrderID orderID;
    dishesFifo.read(static_cast<void *>(&orderID), sizeof orderID);
    return orderID;
}
