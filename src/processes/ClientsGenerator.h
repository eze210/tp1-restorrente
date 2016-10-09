//
// Created by fabrizio on 09/10/16.
//

#ifndef RESTORRENTE_CLIENTSGENERATOR_H
#define RESTORRENTE_CLIENTSGENERATOR_H


#include <utils/MyProcess.h>

class ClientsGenerator : public MyProcess{
public:
    ClientsGenerator();
    ~ClientsGenerator();
    int run();
};


#endif //RESTORRENTE_CLIENTSGENERATOR_H
