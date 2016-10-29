#ifndef RESTORRENTE_LIGHTHANDLER_H
#define RESTORRENTE_LIGHTHANDLER_H

#include <utils/EventHandler.h>

class LightHandler : public EventHandler {
private:
	bool &powerFailure;

public:
	explicit LightHandler(bool &powerFailure);
    int handleSignal(int signalNumber);
    ~LightHandler();
};

#endif
