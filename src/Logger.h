#ifndef LOGGER_H_
#define LOGGER_H_

/** Include area. */
#include "Singleton.h"

#include <iostream>
#include <string>

/** Useful macro to use C useful macros. */
#define LOGGER																	\
	Singleton<logger::Logger>::instance() <<									\
	"[" << Singleton<logger::Logger>::instance().getLevelAsString() << "] " <<	\
	"{" __DATE__ " - " __TIME__"} "												\
	"(" << __FILE__ << ":" << __LINE__ << "): "

namespace logger {

/** Possible logging levels. */
typedef enum {
	INFO,
	WARNING,
	ERROR,
	CRITICAL
} LogLevel;

/** End of line. */
static const char endl = '\n';

/** Logger class definition. */
class Logger {
private:
	LogLevel logLevel;
	std::ostream &outputStream;

public:
	Logger();

	template<typename T>
	const Logger& operator<<(const T& message) const {
		outputStream << message;
		return *this;
	}

	const std::string getLevelAsString() const;
	~Logger();
};

};

#endif
