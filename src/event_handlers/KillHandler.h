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
    KillHandler(vector<Table>& tables, vector<Receptionist>& receptionists);
    int handleSignal(int signalNumber);
    ~KillHandler();

private:
    vector<Table>& tables;
    vector<Receptionist>& receptionists;
};


#endif //RESTORRENTE_KILLHANDLER_H
