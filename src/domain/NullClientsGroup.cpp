//
// Created by fabrizio on 09/10/16.
//

#include "NullClientsGroup.h"

NullClientsGroup::NullClientsGroup() { }

NullClientsGroup::NullClientsGroup(int id) {
    this->id = id;
}

NullClientsGroup NullClientsGroup::BuildClientsGroup(int id) {
    return NullClientsGroup(id);
}

bool NullClientsGroup::notNull() {
    return false;
}
