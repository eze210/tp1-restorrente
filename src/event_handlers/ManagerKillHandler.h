//
// Created by fabrizio on 23/10/16.
//

#ifndef RESTORRENTE_MANAGERKILLHANDLER_H
#define RESTORRENTE_MANAGERKILLHANDLER_H


#include <utils/EventHandler.h>

class ManagerKillHandler : public EventHandler {
public:
    ManagerKillHandler();
    int handleSignal(int signalNumber);
    ~ManagerKillHandler();
};


#endif //RESTORRENTE_MANAGERKILLHANDLER_H
