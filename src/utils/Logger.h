#ifndef LOGGER_H_
#define LOGGER_H_

/** Include area. */
#include "Clock.h"
#include "Singleton.h"
#include "LockFile.h"

#include <iostream>
#include <string>
#include <chrono>
#include <sys/time.h>
#include <sstream>


/** Useful macro to use C useful macros. */
#define LOGGER                                                                 \
    Singleton<logger::Logger>::instance() <<                                   \
    "[" << Singleton<logger::Logger>::instance().getLevelAsString() << getpid() << "] "    \
    "{" << Singleton<restoclock::Clock>::instance().getNanosecondsAsString() << "}: "

namespace logger {

    static const char *LOG_FILE = "./restorrente.log";
    static LockFile loggingLock(LOG_FILE);

/** Possible logging levels. */
    typedef enum {
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    } LogLevel;

/** TODO: If needed, investigate how to use manipulators correctly in
 * 	non-standard class.
 * 	Temporarily, we define the end of line dummy way. */
    static const char endl = '\n';

/** Logger class definition. */
    class Logger {
    private:
        LogLevel logLevel;
        std::ostream &outputStream;

        class ConditionallyUnlockedScope {
        private:
        	LockFile &lock;
        	bool unlock;
        public:
        	ConditionallyUnlockedScope(LockFile &lock, bool unlock);
        	~ConditionallyUnlockedScope();
        };

    public:
        Logger();

        void logToFile(const std::string &message) const {
        	LockFile l("log.txt");
        	l.tomarLock();
        	l.escribir(message.c_str(), message.length());
        	l.liberarLock();
        }

        template<typename T>
        const Logger &operator<<(const T &message) const {
            struct timeval tv;
            struct timezone tz;
            gettimeofday(&tv, &tz);
            ConditionallyUnlockedScope(loggingLock, false);
        	std::stringstream ss;
        	ss << message;
        	logToFile(ss.str());
            outputStream << message;
            return *this;
        }


        /* Only unlocked when given a logger::endl character! */
        const Logger &operator<<(const char message) const {
            ConditionallyUnlockedScope(loggingLock, message == logger::endl);
        	std::stringstream ss;
        	ss << message;
        	logToFile(ss.str());
            outputStream << message;
        	return *this;
        }

        const std::string getLevelAsString() const;

        ~Logger();
    };

}

#endif
