#ifndef RESTORRENTE_MANAGER_H
#define RESTORRENTE_MANAGER_H

#include "MyProcess.h"
#include "../utils/SharedMemory.h"

class Manager : public MyProcess {
public:
    Manager();
    int run();
    void stop();
    ~Manager();
private:
    SharedMemory<bool> working;
};

#endif
