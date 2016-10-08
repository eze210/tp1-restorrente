#include "Table.h"
#include "LobbyMonitor.h"

Table::Table() : keepAlive(true) {
}

int Table::run() {
    while (keepAlive) {
        ClientsGroup clients = LobbyMonitor::getInstance().getClients();
        clients.eat();
        keepAlive = false;
    }
    return 0;
}

Table::~Table() {
}

