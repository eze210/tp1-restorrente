#include "KillHandler.h"

#include "Logger.h"
#include "CashRegister.h"

#include <csignal>

#define SIGNAL_KILL 2
KillHandler::KillHandler(){
}

int KillHandler::handleSignal(int signalNumber) {
    if (signalNumber == SIGINT) {
        LOGGER << "KILL---------------" << signalNumber << logger::endl;
        LOGGER << "SE PRODUJO UN CORTE DE LUZ" << logger::endl;
        LOGGER << "DINERO EN CAJA: " <<
        		CashRegister::getInstance().getMoneyInCashRegister() <<
				logger::endl;
        LOGGER << "DINERO SIN COBRAR: " <<
        		CashRegister::getInstance().getUncollectedMoney() <<
				logger::endl;
        LobbyMonitor::getInstance().clear();
        CashRegister::getInstance().clearUncollectedMoney();
    } else if (signalNumber == SIGKILL) {
        exit(0);
    }
    return 0;
}

KillHandler::~KillHandler() {
}
