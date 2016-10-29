#include <csignal>
#include "LightHandler.h"

#define SIGNAL_KILL 2
LightHandler::LightHandler(bool &powerFailure) :
powerFailure(powerFailure) {
}

int LightHandler::handleSignal(int signalNumber) {
    if (signalNumber == SIGINT) {
    	powerFailure = true;
    }
    return 0;
}

LightHandler::~LightHandler() {
}
