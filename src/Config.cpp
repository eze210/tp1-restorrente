//
// Created by fabrizio on 08/10/16.
//

#include <iostream>
#include <fstream>
#include "Config.h"
#include <sstream>

using std::ifstream;
using std::cout;
using std::string;
using std::istringstream;


Config::Config() {
    Config::loaded = false;
    Config::receptionists = 0;
    Config::waiters = 0;
    Config::tables = 0;
    Config::foods = vector<Food>();
}


void Config::loadConfig() {
    if (loaded)
        return;
    Config();
    ifstream conf;
    conf.open ("./data/conf");
    if (!conf.is_open()) {
        cout << "No se pudo abrir el archivo";
        return;
    }
    try {
        receptionists = std::stoi(getNextConfValue(conf));
        waiters = std::stoi(getNextConfValue(conf));
        tables = std::stoi(getNextConfValue(conf));
        foods = getFoodsFromLine(getNextConfValue(conf));
        loaded = true;
    } catch (const ifstream::failure& e){
        cout << "Error leyendo el archivo";
        loaded = false;
    }
    if ((conf) && (conf.is_open())) {
        conf.close();
    }
}

int Config::getReceptionistsCount() {
    return receptionists;
}

int Config::getWaitersCount() {
    return waiters;
}

int Config::getTablesCount() {
    return tables;
}

vector<Food> Config::getAvailableFoods() {
    return foods;
}


string Config::getNextConfValue(ifstream& conf) {
    string line;
    getline(conf, line);
    return line.substr(line.find('='), string::npos);
}

vector<Food> Config::getFoodsFromLine(string line) {
    vector<Food> foodsVector;
    istringstream stream(line);
    string food;
    while (getline(stream, food, ',')) {
        food.erase(0,1);
        istringstream f(food);
        string foodName;
        string foodCost;
        getline(stream, foodName, ',');
        getline(stream, foodCost, ',');
        int cost = std::stoi(foodCost);
        foodsVector.push_back(Food(foodName, cost));
    }
    return foodsVector;
}
