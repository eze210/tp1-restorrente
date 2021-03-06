#ifndef RECEPTIONIST_H_
#define RECEPTIONIST_H_

#include "MyProcess.h"
#include "DoorOutside.h"
#include "LobbyMonitor.h"
#include "DoorInside.h"

typedef char ReceptionistID;

class Receptionist : public MyProcess {
private:
	DoorInside& door;
	Semaphore doorSemaphore;

public:
	explicit Receptionist(DoorInside& aDoor);
	int run();
	virtual ~Receptionist();
};

#endif
