//
// Created by fabrizio on 08/10/16.
//

#include "data/Config.h"
#include <vector>

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
    return 0;
}
