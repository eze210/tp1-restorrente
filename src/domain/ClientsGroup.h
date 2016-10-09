#ifndef CLIENTSGROUP_H_
#define CLIENTSGROUP_H_

#include <unistd.h>
#include <vector>
#include <string>
#include "Food.h"

using std::string;
using std::vector;

class ClientsGroup {
protected:
    int id;
    vector<Food> order;
    ClientsGroup();
public:
    explicit ClientsGroup(int id);
    static ClientsGroup BuildClientsGroup(int id);
    ClientsGroup& addOrder(Food food);
    const ClientsGroup& addOrder(Food food) const;
    void eat();
    vector<Food> getOrder();
    float getTotalCost();
    const char *serialize();
    virtual bool notNull();
};

#endif
