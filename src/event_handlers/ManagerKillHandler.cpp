//
// Created by fabrizio on 23/10/16.
//

#include <csignal>
#include <cstdlib>
#include <processes/Manager.h>
#include "ManagerKillHandler.h"

ManagerKillHandler::ManagerKillHandler() {
}

int ManagerKillHandler::handleSignal(int signalNumber) {
    if (signalNumber == SIGKILL) {
        exit(0);
    } else if (signalNumber == SIGINT) {
        return 0;
    }
    return 0;
}

ManagerKillHandler::~ManagerKillHandler() {
}