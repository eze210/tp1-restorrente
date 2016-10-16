#ifndef CLIENTSGROUP_H_
#define CLIENTSGROUP_H_

#include <unistd.h>
#include <vector>
#include <string>
#include "Food.h"
#include "Order.h"
#include <cstdint>

typedef uint32_t ClientID;

class ClientsGroup {
private:
    ClientID id;
    std::vector<Food> order;
    ClientsGroup() = delete;

public:
    explicit ClientsGroup(ClientID id);
    ClientID getID() const;
    ClientsGroup& addOrder(Food food);
    const ClientsGroup& addOrder(Food food) const;
    void eat();
    OrderID getOrder();
    float getTotalCost();
    const char *serialize();
    bool isValid();

    static const ClientID invalidClientID;
};

#endif
