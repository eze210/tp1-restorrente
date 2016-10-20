//
// Created by fabrizio on 20/10/16.
//

#include <utils/Logger.h>
#include <csignal>
#include "KillHandler.h"

const static std::string cajaMem("caja.mem");
const static std::string noCobradoMem("no-cobrado.mem");

#define SIGNAL_KILL 2
KillHandler::KillHandler(SharedMemory<int>& laCaja, SharedMemory<int>& loNoCobrado) :
        caja(laCaja), dineroPorCobrar(loNoCobrado) {
}

int KillHandler::handleSignal(int signalNumber) {
    caja.create(cajaMem,1);
    dineroPorCobrar.create(noCobradoMem,2);
    LOGGER << "KILL---------------" << signalNumber <<logger::endl;
    if (signalNumber == SIGINT) {
        LOGGER << "SE PRODUJO UN CORTE DE LUZ" << logger::endl;
        LOGGER << "DINERO EN CAJA: " << caja.read() << logger::endl;
        LOGGER << "DINERO SIN COBRAR: " << dineroPorCobrar.read() << logger::endl;
        caja.free();
        dineroPorCobrar.free();
        exit(0);
    }
    return 0;
}

KillHandler::~KillHandler() {
}
