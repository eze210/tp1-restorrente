#ifndef FIFO_H_
#define FIFO_H_

#include <string>
#include <cstdint>
#include "OSException.h"
#include "Mutex.h"

class Fifo {
protected:
	const std::string fileName;
	int fileDescriptor;
    Mutex mutex;

public:
	explicit Fifo(const std::string &fileName);
	virtual ~Fifo();
	virtual void open() {}
	void close();
	void release();

	static const int invalidFileDescriptor;
};

#endif
