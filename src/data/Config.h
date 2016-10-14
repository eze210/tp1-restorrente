#ifndef RESTORRENTE_CONFIG_H
#define RESTORRENTE_CONFIG_H

#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include <iostream>
#include "Food.h"

class Config {
private:
    Config();
    static bool loaded;
    static int receptionists;
    static int waiters;
    static int tables;
    static std::vector<Food> foods;
    static std::vector<Food> getFoodsFromLine(const std::string &line);
    static std::string getNextConfValue(std::ifstream& conf);

public:
    static void loadConfig();
    static int getReceptionistsCount();
    static int getWaitersCount();
    static int getTablesCount();
    static std::vector<Food>& getAvailableFoods();
};

#endif
