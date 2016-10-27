//
// Created by fabrizio on 26/10/16.
//

#ifndef RESTORRENTE_OTHERDOOR_H
#define RESTORRENTE_OTHERDOOR_H


#include <utils/Fifos/FifoRead.h>
#include <domain/ClientsGroup.h>

class DoorInside {
private:
    FifoRead doorFifo;

public:
    DoorInside();
    ClientsGroup getClients();
    void releaseFifo();
    ~DoorInside();
};


#endif //RESTORRENTE_OTHERDOOR_H
