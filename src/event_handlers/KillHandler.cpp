#include "KillHandler.h"

#include "Logger.h"
#include "CashRegister.h"

#include <csignal>

#define SIGNAL_KILL 2
KillHandler::KillHandler(){
}

int KillHandler::handleSignal(int signalNumber) {
    if (signalNumber == SIGINT) {
        LOGGER << logger::endl;
        LOGGER << "SE PRODUJO UN CORTE DE LUZ--------------------" << logger::endl;
        LOGGER << "DINERO EN CAJA: " <<
        		CashRegister::getInstance().getMoneyInCashRegister() <<
				logger::endl;
        LOGGER << "DINERO SIN COBRAR: " <<
        		CashRegister::getInstance().getUncollectedMoney() <<
				logger::endl;
        LOGGER << logger::endl;
        LobbyMonitor::getInstance().openForRead();
        LobbyMonitor::getInstance().clear();
        LOGGER << "LOBBY EVACUADO" << logger::endl;
//        CashRegister::getInstance().clearUncollectedMoney();
//        exit(0);
    }
    return 0;
}

KillHandler::~KillHandler() {
}
