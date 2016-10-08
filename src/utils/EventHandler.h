#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

class EventHandler {
public:
    virtual int handleSignal(int signalNumber) = 0;
    virtual ~EventHandler() { }
};

#endif
