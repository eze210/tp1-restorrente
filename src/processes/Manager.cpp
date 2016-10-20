//
// Created by fabrizio on 20/10/16.
//

#include <utils/Logger.h>
#include <LobbyMonitor.h>
#include "Manager.h"

const static std::string cajaMem("caja.mem");
const static std::string noCobradoMem("no-cobrado.mem");

Manager::Manager() : caja(cajaMem,1), dineroPorCobrar(noCobradoMem,2){ }


int Manager::run() {
    while (true) {
        sleep(2);
        LOGGER << "GERENTE CONSULTA:" << logger::endl;
        LOGGER << "DINERO EN CAJA: " << caja.read() << logger::endl;
        LOGGER << "DINERO SIN COBRAR: " << dineroPorCobrar.read() << logger::endl;
        LOGGER << "CANTIDAD DE PERSONAS EN EL LOBBY: " << LobbyMonitor::getInstance().getNumberOfClientsInLobby() << logger::endl;
    }
    return 0;
}

Manager::~Manager() { }