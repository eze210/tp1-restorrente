//
// Created by fabrizio on 26/09/16.
//

#include "ClientsGroup.h"
#include <string>

ClientsGroup::ClientsGroup(int id) : id(id) {
}

void ClientsGroup::eat() {
    sleep(1);
}

const char *ClientsGroup::serialize() {
    string serial = "[" + order.at(0).serialize();
    for (size_t i = 1; i < order.size(); i++) {
        serial += "," + order.at(i).serialize();
    }
    serial += "]";
    return serial.c_str();
}
