#ifndef RESTORRENTE_CLIENTSGENERATOR_H
#define RESTORRENTE_CLIENTSGENERATOR_H

#include "MyProcess.h"

class ClientsGenerator : public MyProcess {
public:
    explicit ClientsGenerator(ClientID clientsCount);
    ~ClientsGenerator();
    int run();

private:
    ClientID clientsCount;
};

#endif
