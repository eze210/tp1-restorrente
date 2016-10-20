#include <string>
#include <utils/Logger.h>
#include <csignal>
#include "TableKillHandler.h"

#define SIGNAL_KILL 2
const static std::string cajaMem("caja.mem");
const static std::string noCobradoMem("no-cobrado.mem");

TableKillHandler::TableKillHandler() {
	caja.create(cajaMem,1);
	dineroPorCobrar.create(noCobradoMem,2);
}

int TableKillHandler::handleSignal(int signalNumber) {
	LOGGER << "SE PRODUJO UN CORTE DE LUZ" << logger::endl;
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

TableKillHandler::~TableKillHandler() { 
}
