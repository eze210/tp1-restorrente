#include "ClientsGroup.h"
#include <string>
#include <vector>
#include "Food.h"

const ClientID ClientsGroup::invalidClientID = -1;

ClientsGroup::ClientsGroup(ClientID id) : id(id) {
}

ClientID ClientsGroup::getID() const {
	return id;
}

const ClientsGroup& ClientsGroup::addOrder(Food food) const {
    return *this;
}

ClientsGroup& ClientsGroup::addOrder(Food food) {
    order.push_back(food);
    return *this;
}

void ClientsGroup::eat() {
    sleep(1);
}

std::vector<Food> ClientsGroup::getOrder() {
    return order;
}

float ClientsGroup::getTotalCost() {
    float total = 0;
    for (size_t i = 0; i < order.size(); i++) {
        total += order.at(i).getCost();
    }
    return total;
}

const char *ClientsGroup::serialize() {
    std::string serial = "[" + order.at(0).serialize();
    for (size_t i = 1; i < order.size(); i++) {
        serial += "," + order.at(i).serialize();
    }
    serial += "]";
    return serial.c_str();
}

bool ClientsGroup::isValid() {
    return id != invalidClientID;
}
