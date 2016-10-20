#ifndef TABLEKILLHANDLER_H_
#define TABLEKILLHANDLER_H_

#include <utils/SharedMemory.h>
#include "../utils/EventHandler.h"


class TableKillHandler : public EventHandler {
public:
    TableKillHandler();
    int handleSignal(int signalNumber);
    ~TableKillHandler();

private:
    SharedMemory<int> caja;
    SharedMemory<int> dineroPorCobrar;
};

#endif
