/* ************************************************************************* *
 * Include Area                                                             *
 * ************************************************************************* */

#include "MyProcess.h"
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>


/* ************************************************************************* *
 * Member Function Definitions                                               *
 * ************************************************************************* */

/** Starts a child process which executes the run virtual function.
 */
void MyProcess::start() {
	pid = fork();

	/* the child process will exit with the return value of run */
	if (pid == 0)
		exit(run());
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


/** Virtual default destructor.
 */
MyProcess::~MyProcess() {
}

