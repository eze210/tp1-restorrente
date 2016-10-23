//
// Created by fabrizio on 20/10/16.
//

#ifndef RESTORRENTE_KILLHANDLER_H
#define RESTORRENTE_KILLHANDLER_H


#include <utils/EventHandler.h>
#include <Table.h>
#include <Receptionist.h>

class KillHandler : public EventHandler {
public:
    KillHandler();
    int handleSignal(int signalNumber);
    ~KillHandler();
};


#endif //RESTORRENTE_KILLHANDLER_H
