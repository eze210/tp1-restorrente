#include <event_handlers/ManagerKillHandler.h>
#include <csignal>
#include <utils/SignalHandler.h>
#include "Manager.h"

#include "Logger.h"
#include "LobbyMonitor.h"
#include "CashRegister.h"

Manager::Manager() : working(__FILE__,1) {
    working.write(true);
}

int Manager::run() {

    while (working.read()) {
        sleep(3);
        LOGGER << logger::endl;
        LOGGER << "GERENTE CONSULTA:" << logger::endl;
        LOGGER << "DINERO EN CAJA: " << CashRegister::getInstance().getMoneyInCashRegister() << logger::endl;
        LOGGER << "DINERO SIN COBRAR: " << CashRegister::getInstance().getUncollectedMoney() << logger::endl;
        LOGGER << "CANTIDAD DE PERSONAS EN EL LOBBY: " << LobbyMonitor::getInstance().getNumberOfClientsInLobby() << logger::endl;
        LOGGER << logger::endl;
    }
    return 0;
}


void Manager::stop() {
    working.write(false);
    this->wait();
    working.free();
}

Manager::~Manager() {

}
