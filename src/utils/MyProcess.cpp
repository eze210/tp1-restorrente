/* ************************************************************************* *
 * Include Area                                                             *
 * ************************************************************************* */

#include "MyProcess.h"
#include "OSException.h"
#include <sys/wait.h>


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
    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
}

void MyProcess::receiveSignal(int signal) {
    raise(signal);
}


/** Virtual default destructor.
 */
MyProcess::~MyProcess() {
}

