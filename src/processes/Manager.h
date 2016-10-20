//
// Created by fabrizio on 20/10/16.
//

#ifndef RESTORRENTE_MANAGER_H
#define RESTORRENTE_MANAGER_H


#include <utils/MyProcess.h>
#include <utils/SharedMemory.h>

class Manager : public MyProcess {
public:
    Manager();
    int run();
    ~Manager();
private:
    SharedMemory<int> caja;
    SharedMemory<int> dineroPorCobrar;
};


#endif //RESTORRENTE_MANAGER_H
