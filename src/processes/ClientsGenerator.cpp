//
// Created by fabrizio on 09/10/16.
//

#include <Door.h>
#include <data/Config.h>
#include <vector>
#include <domain/NullClientsGroup.h>
#include "ClientsGenerator.h"

#define CLIENTS_COUNT 10

ClientsGenerator::ClientsGenerator() { }

ClientsGenerator::~ClientsGenerator() { }

int ClientsGenerator::run() {
    int i = 0;
    Door door;
    vector<ClientsGroup> clientsList;
    while (i < CLIENTS_COUNT) {
        vector<Food> foods = Config::getAvailableFoods();
        Food food = foods.at(i % foods.size());
        ClientsGroup clients
                = ClientsGroup::BuildClientsGroup(i).addOrder(food);
        std::cout << clients.serialize() << std::endl;
        clientsList.push_back(clients);
        door.addClients(clients);
        i++;
    }
    NullClientsGroup nullClient(0);
    door.addClients(nullClient);
    return 0;
}
