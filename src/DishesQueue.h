//
// Created by fabrizio on 16/10/16.
//

#ifndef RESTORRENTE_DISHESQUEUE_H
#define RESTORRENTE_DISHESQUEUE_H


class DishesQueue {
public:
    void addPreparedDish(OrderID orderID);
    OrderID getPreparedDish();
    static DishesQueue& getInstance();
    ~DishesQueue();
private:
    DishesQueue();
    Fifo dishesFifo;
    static DishesQueue instance;
};


#endif //RESTORRENTE_DISHESQUEUE_H
