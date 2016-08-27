#ifndef EXAMPLEPROCESS_H_
#define EXAMPLEPROCESS_H_

#include "MyProcess.h"

class ExampleProcess : public MyProcess{
public:
	virtual int run();
	virtual ~ExampleProcess();
};

#endif
