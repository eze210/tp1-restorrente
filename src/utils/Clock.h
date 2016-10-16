#ifndef CLOCK_H_
#define CLOCK_H_

#include <string>

namespace restoclock {

    class Clock {
    public:
        const long getNanoseconds() const;
        const std::string getNanosecondsAsString() const;
    };

}

#endif
