#ifndef SIGNALHANDLER_H_
#define SIGNALHANDLER_H_

#include <csignal>
#include <cstdio>
#include <memory.h>
#include <vector>

#include "EventHandler.h"

/** Singleton signal handler. */
class SignalHandler {
private:
    /** Static method to preserve signature 'void (*)(int)'. */
    static void staticDispatcher(int signum);

    /** Instance's dispatcher method. */
    void dispatcher(int signum);

    /** Registered signal handlers. */
    std::vector<EventHandler *> signalHandlers;

    /** Copy constructor is private (In c++11, we could use delete modifier). */
    SignalHandler(const SignalHandler &);

    SignalHandler &operator=(const SignalHandler &);

    /** Private constructor, it is a singleton. */
    SignalHandler();

public:
    /** Returns a reference to static instance of the singleton. */
    static SignalHandler &getInstance();

    /** Modifies the action associated to the specified signal number. */
    EventHandler *registerHandler(int signalNumber, EventHandler *eventHandler);

    /** Start to ignore the specified signal number.
     * 	Note: this method does not restore the default handler. */
    int removeHandler(int signalNumber);
};

#endif
