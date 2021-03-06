/** Include area. */
#include "Logger.h"
#include <string>

namespace logger {

/** Possible log levels as C strings. */
    static const char *levelTags[] = {
            "INFO",
            "WARNING",
            "ERROR",
            "CRITICAL"
    };

/**	TODO: Allow to use another file.
 */
    Logger::Logger() :
            logLevel(INFO),
            outputStream(std::cout) {
    }

/**	TODO: Close the file if it is not a standard flow (stdout, stderr).
 */
    Logger::~Logger() {
    }

/** Returns the current log level as string.
 *
 *	\return A string with the current logging level.
 */
    const std::string Logger::getLevelAsString() const {
        return levelTags[logLevel];
    }

    /**
     *
     */
    Logger::ConditionallyUnlockedScope
          ::ConditionallyUnlockedScope(LockFile &lock, bool unlock) :
            lock(lock),
            unlock(unlock) {
        lock.tomarLock();
    }

    /**
     *
     */
    Logger::ConditionallyUnlockedScope::~ConditionallyUnlockedScope() {
        if (unlock)
            lock.liberarLock();
    }

}
