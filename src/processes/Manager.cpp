#include "Manager.h"

#include "Logger.h"
#include "LobbyMonitor.h"
#include "CashRegister.h"

Manager::Manager() {
}

int Manager::run() {
    for(int i= 0; i< 5; ++i) {
        sleep(2);
        LOGGER << "GERENTE CONSULTA:" << logger::endl;
        LOGGER << "DINERO EN CAJA: " << CashRegister::getInstance().getMoneyInCashRegister() << logger::endl;
        LOGGER << "DINERO SIN COBRAR: " << CashRegister::getInstance().getUncollectedMoney() << logger::endl;
        LOGGER << "CANTIDAD DE PERSONAS EN EL LOBBY: " << LobbyMonitor::getInstance().getNumberOfClientsInLobby() << logger::endl;
    }
    return 0;
}

Manager::~Manager() { }
