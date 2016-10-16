//
// Created by fabrizio on 15/10/16.
//

#ifndef RESTORRENTE_WAITER_H
#define RESTORRENTE_WAITER_H


#include <utils/MyProcess.h>
#include <WaitersQueue.h>

class Waiter {
public:
    explicit Waiter(uint32_t waiterID);
    ~Waiter();
    void addOrder(uint32_t tableID, OrderID order);
    OrderID getDish(uint32_t tableID);
    void setID(uint32_t waiterID);
    uint32_t getID();
private:
    uint32_t id;
};


#endif //RESTORRENTE_WAITER_H
