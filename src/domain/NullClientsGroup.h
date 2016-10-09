//
// Created by fabrizio on 09/10/16.
//

#ifndef RESTORRENTE_NULLCLIENTSGROUP_H
#define RESTORRENTE_NULLCLIENTSGROUP_H


#include "ClientsGroup.h"

class NullClientsGroup : public ClientsGroup {
public:
    explicit NullClientsGroup(int id);
    static NullClientsGroup BuildClientsGroup(int id);
    bool notNull();

private:
    NullClientsGroup();
};


#endif //RESTORRENTE_NULLCLIENTSGROUP_H
