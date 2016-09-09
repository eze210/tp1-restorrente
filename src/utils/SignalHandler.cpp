#include "SignalHandler.h"

SignalHandler::SignalHandler() : signalHandlers(NSIG, NULL) {
}

SignalHandler& SignalHandler::getInstance() {
	static SignalHandler instance;
	return instance;
}

EventHandler* SignalHandler::registerHandler(int signalNumber, EventHandler* eventHandler) {
	EventHandler* oldEventHandler = signalHandlers[signalNumber];
	signalHandlers[signalNumber] = eventHandler;

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));

	/* sets the signal handler */
	sa.sa_handler = SignalHandler::staticDispatcher;

	/* initializes as empty the mask of signals to be blocked
	 * during handler execution */
	sigemptyset(&sa.sa_mask);

	/* adds the signal number to the mask */
	sigaddset(&sa.sa_mask, signalNumber);

	/* applies the changes in signal action */
	sigaction(signalNumber, &sa, 0);

	return oldEventHandler;
}

void SignalHandler::staticDispatcher(int signalNumber) {
	SignalHandler::getInstance().dispatcher(signalNumber);
}

void SignalHandler::dispatcher(int signalNumber) {
	if (signalHandlers[signalNumber] != NULL)
		signalHandlers[signalNumber]->handleSignal(signalNumber);
}

int SignalHandler::removeHandler(int signalNumber) {
	signalHandlers[signalNumber] = NULL;
	return 0;
}
