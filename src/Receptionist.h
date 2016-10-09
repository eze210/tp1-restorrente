#ifndef RECEPTIONIST_H_
#define RECEPTIONIST_H_

#include "MyProcess.h"
#include "Door.h"
#include "LobbyMonitor.h"

class Receptionist : public MyProcess {
private:
    Door &door;
    LobbyMonitor &lobbyMonitor;
    SharedMemory<bool> restaurantOpen;
public:
    Receptionist(Door &door, LobbyMonitor &lobbyMonitor);
    int run();
    virtual ~Receptionist();
};

#endif
