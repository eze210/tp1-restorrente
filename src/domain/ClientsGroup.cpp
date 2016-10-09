//
// Created by fabrizio on 26/09/16.
//

#include "ClientsGroup.h"
#include <string>
#include <vector>
#include "Food.h"

ClientsGroup::ClientsGroup() { }

ClientsGroup::ClientsGroup(int id) : id(id) {
}

ClientsGroup ClientsGroup::BuildClientsGroup(int id) {
    return ClientsGroup(id);
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

vector<Food> ClientsGroup::getOrder() {
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
    string serial = "[" + order.at(0).serialize();
    for (size_t i = 1; i < order.size(); i++) {
        serial += "," + order.at(i).serialize();
    }
    serial += "]";
    return serial.c_str();
}

bool ClientsGroup::notNull() {
    return true;
}
