//
// Created by fabrizio on 15/10/16.
//

#ifndef RESTORRENTE_SEMAPHORE_H
#define RESTORRENTE_SEMAPHORE_H

#include "Semaforo.h"
#include <string>

class Semaphore {
private:
    Semaforo instance;
public:
    Semaphore(const std::string &nombre, const int valorInicial);
    ~Semaphore();
    int p();
    int v();
    void erase() const;
};

#endif //RESTORRENTE_SEMAPHORE_H
