//
// Created by fabrizio on 26/09/16.
//

#include "Food.h"
#include <string>

Food::Food(string desc, float cost) {
    this->description = desc;
    this->cost = cost;
}

const string Food::serialize() const {
    return "("
           + description
           + "," + std::to_string(cost)
           //+ "," + std::to_string(preparationTime)
           + ")";
}

Food::~Food() { }
