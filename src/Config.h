//
// Created by fabrizio on 08/10/16.
//

#ifndef RESTORRENTE_CONFIG_H
#define RESTORRENTE_CONFIG_H

#include <vector>
#include <tuple>
#include <fstream>
#include <iostream>
#include <domain/Food.h>

using std::vector;
using std::tuple;
using std::ifstream;

class Config {
private:
    Config();
    static bool loaded;
    static int receptionists;
    static int waiters;
    static int tables;
    static vector<Food> foods;
    static vector<Food> getFoodsFromLine(string line);
    static string getNextConfValue(ifstream& conf);
public:
    static void loadConfig();
    static int getReceptionistsCount();
    static int getWaitersCount();
    static int getTablesCount();
    static vector<Food> getAvailableFoods();
};


#endif //RESTORRENTE_CONFIG_H
