#include "Food.h"
#include <string>

Food::Food(const std::string &desc, float cost) :
    description(desc),
    cost(cost) {
}

std::string Food::getDescription() {
    return description;
}

float Food::getCost() {
    return cost;
}

const std::string Food::serialize() const {
    return "("
           + description
           + "," + std::to_string(cost)
           //+ "," + std::to_string(preparationTime)
           + ")";
}

Food::~Food() { }
