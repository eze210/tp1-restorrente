//
// Created by fabrizio on 23/10/16.
//

#include <csignal>
#include <cstdlib>
#include "ManagerKillHandler.h"

ManagerKillHandler::ManagerKillHandler() {
}

int ManagerKillHandler::handleSignal(int signalNumber) {
    if (signalNumber == SIGKILL) {
        exit(0);
    }
    return 0;
}

ManagerKillHandler::~ManagerKillHandler() {
}