#ifndef RESTORRENTE_WAITER_H
#define RESTORRENTE_WAITER_H

#include "WaitersQueue.h"
#include "Kitchen.h"

class Waiter {
private:
    Kitchen& kitchen;
    WaitersQueue &queue;

public:
    Waiter(Kitchen& theKitchen, WaitersQueue &queue);
    int addOrder(uint32_t tableID, OrderID order);
    ~Waiter();
};

#endif
