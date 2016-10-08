#ifndef DOOR_H_
#define DOOR_H_

#include <domain/ClientsGroup.h>

class Door {
public:
	Door();
	ClientsGroup getClients();
	void addClients(ClientsGroup &clients);
	~Door();
};

#endif
