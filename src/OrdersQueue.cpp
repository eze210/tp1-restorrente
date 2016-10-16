//
// Created by fabrizio on 15/10/16.
//

#include <string>
#include <domain/Order.h>
#include <utils/Fifos/FifoRead.h>
#include <utils/Fifos/FifoWrite.h>
#include "OrdersQueue.h"

/** Name to represent the fifo in the file system. */
const static std::string orderFifoName("order.fifo");

OrdersQueue& OrdersQueue::getInstance() {
    static OrdersQueue instance;
    return instance;
}

OrdersQueue::OrdersQueue() : ordersFifo(orderFifoName) {}

OrdersQueue::~OrdersQueue() {}

void OrdersQueue::addNewOrder(OrderID orderID) {
    /* fifo instance that only exists if the process uses this method */
    static FifoWrite ordersFifo(orderFifoName);
    /* puts the id in the fifo */
    ordersFifo.write(static_cast<const void *>(&orderID), sizeof orderID);
}

OrderID OrdersQueue::getOrder() {
    /* fifo instance that only exists if the process uses this method */
    static FifoRead ordersFifo(orderFifoName);
    /* blocks until an order id is ready to be read */
    OrderID orderID;
    ordersFifo.read(static_cast<void *>(&orderID), sizeof orderID);
    return orderID;
}
