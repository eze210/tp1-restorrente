#ifndef RESTORRENTE_MANAGER_H
#define RESTORRENTE_MANAGER_H

#include "MyProcess.h"

class Manager : public MyProcess {
public:
    Manager();
    int run();
    ~Manager();
};

#endif
