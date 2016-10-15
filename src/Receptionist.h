#ifndef RECEPTIONIST_H_
#define RECEPTIONIST_H_

#include "MyProcess.h"
#include "Door.h"
#include "SharedMemory.h"
#include "LobbyMonitor.h"

typedef char ReceptionistID;

class Receptionist : public MyProcess {
private:
	Door &door;
	SharedMemory<bool> restaurantOpen;

public:
	explicit Receptionist(Door &door);
	int run();
	virtual ~Receptionist();
};

#endif
