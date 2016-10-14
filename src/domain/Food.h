#ifndef TP1_RESTORRENTE_FOOD_H
#define TP1_RESTORRENTE_FOOD_H

#include <string>

class Food {
public:
    Food(const std::string &desc, float cost);
    std::string getDescription();
    //int getPreparationTime();
    float getCost();
    const std::string serialize() const;
    ~Food();
private:
    std::string description;
    //int preparationTime;
    float cost;
};


#endif //TP1_RESTORRENTE_FOOD_H
