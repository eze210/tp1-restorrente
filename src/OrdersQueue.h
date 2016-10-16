//
// Created by fabrizio on 15/10/16.
//

#ifndef RESTORRENTE_KITCHENQUEUE_H
#define RESTORRENTE_KITCHENQUEUE_H

#include "Fifo.h"
#include "Order.h"

class OrdersQueue {
public:
    void addNewOrder(OrderID orderID);
    OrderID getOrder();
    static OrdersQueue& getInstance();
    ~OrdersQueue();
private:
    OrdersQueue();
    Fifo ordersFifo;
    static OrdersQueue instance;
};


#endif //RESTORRENTE_KITCHENQUEUE_H
