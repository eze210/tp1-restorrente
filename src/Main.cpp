//
// Created by fabrizio on 08/10/16.
//

#include "data/Config.h"
#include "Door.h"
#include "Receptionist.h"
#include <vector>
#include <processes/ClientsGenerator.h>

int main() {
    Config::loadConfig();
    std::cout
        << "Recepcionistas: " << Config::getReceptionistsCount() << std::endl
        << "Mozos: " << Config::getWaitersCount() << std::endl
        << "Mesas: " << Config::getTablesCount()
        << std::endl;

    vector<Food> foods;
    foods = Config::getAvailableFoods();
    std::cout << "Comidas: ";
    for (size_t i = 0; i < foods.size(); i++) {
        std::cout << foods.at(i).serialize() << ";";
    }

    Door door;
    LobbyMonitor monitor = LobbyMonitor::getInstance();
    ClientsGenerator generator;
    vector<Receptionist> receptionists;


    /*for (size_t i = 0; Config::getReceptionistsCount(); i++) {
        Receptionist receptionist(door, monitor);
        receptionist.start();
        receptionists.push_back(receptionist);
    }*/

    Receptionist receptionist(door, monitor);
    receptionist.start();
    generator.start();
    generator.wait();

    receptionist.wait();

    return 0;
}
