//
// Created by fabrizio on 20/10/16.
//

#ifndef RESTORRENTE_PROCESESKILLHANDLER_H
#define RESTORRENTE_PROCESESKILLHANDLER_H


#include <utils/EventHandler.h>


class ProcesesKillHandler : public EventHandler {
public:
    ProcesesKillHandler();
    int handleSignal(int signalNumber);
    ~ProcesesKillHandler();
};


#endif //RESTORRENTE_PROCESESKILLHANDLER_H
