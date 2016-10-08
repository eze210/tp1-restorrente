#ifndef CLIENTSGROUP_H_
#define CLIENTSGROUP_H_

#include <unistd.h>
#include <vector>
#include <string>
#include "Food.h"

using std::string;
using std::vector;

class ClientsGroup {
private:
    int id;
    vector<Food> order;
public:
    explicit ClientsGroup(int id);
    void eat();
    void addOrder(Food food);
    vector<Food> getOrder();
    const char *serialize();
};

#endif
