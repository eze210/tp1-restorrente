//
// Created by fabrizio on 20/10/16.
//

#include <utils/Logger.h>
#include <csignal>
#include "ProcesesKillHandler.h"



#define SIGNAL_KILL 2
ProcesesKillHandler::ProcesesKillHandler() {
}

int ProcesesKillHandler::handleSignal(int signalNumber) {
    if (signalNumber == SIGINT) {
        exit(0);
    }
    return 0;
}

ProcesesKillHandler::~ProcesesKillHandler() {
}
