/* ************************************************************************* *
 * Include Area                                                             *
 * ************************************************************************* */

#include "MyProcess.h"
#include "OSException.h"
#include <sys/wait.h>
#include <iostream>
#include <cerrno>


/* ************************************************************************* *
 * Member Function Definitions                                               *
 * ************************************************************************* */

/** Starts a child process which executes the run virtual function.
 */
void MyProcess::start() {
    pid = fork();

    /* fork error */
    if (pid == -1)
        throw OSException();

    /* the child process will exit with the return value of run */
    if (pid == 0)
        throw run();
}


/** Blocks execution until child process ends, and returns its exit value.
 *
 *	\return The child process exit value.
 */
int MyProcess::wait() {
    int status;
    while (waitpid(pid, &status, 0) == -1) {
    	/* waitpid returns -1 when a signal interrupted the child process.
    	 * That case is not an error for us */
    	if (errno != EINTR)
    		throw OSException();
    }
    return WEXITSTATUS(status);
}

void MyProcess::receiveSignal(int signal) {
    raise(signal);
}


/** Virtual default destructor.
 */
MyProcess::~MyProcess() {
}

