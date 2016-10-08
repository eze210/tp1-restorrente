//
// Created by fabrizio on 26/09/16.
//

#include "Food.h"
#include <string>

const string Food::serialize() const {
    return "("
           + description
           + "," + std::to_string(cost)
           //+ "," + std::to_string(preparationTime)
           + ")";
}

Food::~Food() { }
