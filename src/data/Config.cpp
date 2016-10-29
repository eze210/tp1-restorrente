#include "Config.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

bool Config::loaded;
int Config::receptionists;
int Config::waiters;
int Config::tables;
std::vector<Food> Config::foods;

Config::Config() {
    Config::loaded = false;
    Config::receptionists = 0;
    Config::waiters = 0;
    Config::tables = 0;
    Config::foods = std::vector<Food>();
}

void Config::loadConfig() {
    if (loaded)
        return;
    Config();
    std::ifstream conf;
    conf.open("../src/data/conf");
    if (!conf.is_open()) {
    	std::cout << "No se pudo abrir el archivo" << std::endl;
        return;
    }
    try {
        receptionists = std::stoi(getNextConfValue(conf));
        tables = std::stoi(getNextConfValue(conf));
        waiters = std::stoi(getNextConfValue(conf));
        foods = getFoodsFromLine(getNextConfValue(conf));
        loaded = true;
    } catch (const std::ifstream::failure& e){
    	std::cout << "Error leyendo el archivo" << std::endl;
        loaded = false;
    } catch (const std::invalid_argument& e) {
    	std::cout << "Error parseando archivo" << std::endl;
    }
    if ((conf) && (conf.is_open())) {
        conf.close();
    }
}

int Config::getReceptionistsCount() {
    return receptionists;
}

uint32_t Config::getWaitersCount() {
    return waiters;
}

int Config::getTablesCount() {
    return tables;
}

std::vector<Food>& Config::getAvailableFoods() {
    return foods;
}

std::string Config::getNextConfValue(std::ifstream& conf) {
	std::string line;
    getline(conf, line);
    return line.substr(line.find('=')+1, std::string::npos);
}

std::vector<Food> Config::getFoodsFromLine(const std::string &line) {
    std::vector<Food> foodsVector;
    std::istringstream stream(line);
    std::string food;
    while (getline(stream, food, '|')) {
    	std::istringstream f(food);
    	std::string foodName;
    	std::string foodCost;
        getline(f, foodName, ',');
        getline(f, foodCost, ',');
        float cost = std::stof(foodCost);
        foodsVector.push_back(Food(foodName, cost));
    }
    return foodsVector;
}
