//
// Created by fabrizio on 26/09/16.
//

#ifndef TP1_RESTORRENTE_FOOD_H
#define TP1_RESTORRENTE_FOOD_H

#include <string>

using namespace std;

class Food {

public:
    Food(string desc, int prepTime, float cost);
    string getDescription();
    int getPreparationTime();
    float getCost();
    string serialize();
    ~Food();

private:
    string description;
    int preparationTime;
    float cost;
};


#endif //TP1_RESTORRENTE_FOOD_H
