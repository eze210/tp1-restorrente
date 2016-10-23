#ifndef RESTORRENTE_KITCHEN_H
#define RESTORRENTE_KITCHEN_H

#include "Mutex.h"
#include "Order.h"
#include "WaitersQueue.h"

class Kitchen  {
private:
    Mutex mutex;

public:
    Kitchen();
    void prepareOrder(OrderID order, WaitersQueue &waitersQueue);
    ~Kitchen();
};

#endif
