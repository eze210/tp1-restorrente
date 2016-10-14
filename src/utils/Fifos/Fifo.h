#ifndef FIFO_H_
#define FIFO_H_

#include <string>
#include <cstdint>
#include "OSException.h"

class Fifo {
protected:
	const std::string fileName;
	int fileDescriptor;

public:
	explicit Fifo(const std::string &fileName);
	virtual ~Fifo();
	virtual void open() {}
	void close();
	void release();

	static const int invalidFileDescriptor;
};

#endif
