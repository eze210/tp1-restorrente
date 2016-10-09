//
// Created by fabrizio on 08/10/16.
//

#include "Config.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using std::ifstream;
using std::cout;
using std::string;
using std::istringstream;


bool Config::loaded;
int Config::receptionists;
int Config::waiters;
int Config::tables;
vector<Food> Config::foods;

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
    conf.open("./data/conf");
    if (!conf.is_open()) {
        cout << "No se pudo abrir el archivo" << std::endl;
        return;
    }
    try {
        receptionists = std::stoi(getNextConfValue(conf));
        waiters = std::stoi(getNextConfValue(conf));
        tables = std::stoi(getNextConfValue(conf));
        foods = getFoodsFromLine(getNextConfValue(conf));
        loaded = true;
    } catch (const ifstream::failure& e){
        cout << "Error leyendo el archivo" << std::endl;
        loaded = false;
    } catch (const std::invalid_argument& e) {
        cout << "Error parseando archivo" << std::endl;
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
    return line.substr(line.find('=')+1, string::npos);
}

vector<Food> Config::getFoodsFromLine(string line) {
    vector<Food> foodsVector;
    istringstream stream(line);
    string food;
    while (getline(stream, food, '|')) {
        istringstream f(food);
        string foodName;
        string foodCost;
        getline(f, foodName, ',');
        getline(f, foodCost, ',');
        float cost = std::stof(foodCost);
        foodsVector.push_back(Food(foodName, cost));
    }
    return foodsVector;
}
