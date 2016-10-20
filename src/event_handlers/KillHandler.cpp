//
// Created by fabrizio on 20/10/16.
//

#include <utils/Logger.h>
#include <csignal>
#include "KillHandler.h"

#define SIGNAL_KILL 2
KillHandler::KillHandler(vector<Table>& theTables, vector<Receptionist>& theReceptionists) :
tables(theTables), receptionists(theReceptionists) {
}

int KillHandler::handleSignal(int signalNumber) {
    LOGGER << "KILL---------------" << signalNumber <<logger::endl;
    if (signalNumber == SIGINT) {
        for (size_t i = 0; i < tables.size(); i++) {
            tables.at(i).receiveSignal(SIGINT);
        }
    }
    return 0;
}

KillHandler::~KillHandler() {
}
