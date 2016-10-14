#ifndef RESTORRENTE_CLIENTSGENERATOR_H
#define RESTORRENTE_CLIENTSGENERATOR_H

#include "MyProcess.h"

class ClientsGenerator : public MyProcess {
public:
    ClientsGenerator();
    ~ClientsGenerator();
    int run();
};

#endif
