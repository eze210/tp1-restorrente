#ifndef RANDOMSLEEP_H_
#define RANDOMSLEEP_H_

#include "MyProcess.h"

class RandomSleep: public MyProcess {
private:
	long int random();
	int getId;
	int idx;
public:
	int start(int getId, int idx);
	virtual int run();
	virtual ~RandomSleep();
};

#endif
