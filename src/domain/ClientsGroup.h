#ifndef CLIENTSGROUP_H_
#define CLIENTSGROUP_H_

#include <unistd.h>
#include <vector>
#include "Food.h"

using namespace std;

class ClientsGroup {

private:
	int id;
    vector<Food> order;
public:
	ClientsGroup(int id);
	void eat();
	void addOrder(Food food);
	vector<Food> getOrder();
	const char* serialize();
};

#endif
