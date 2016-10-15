#include "Clock.h"

#include <time.h>
#include <sstream>

namespace restoclock {

   const long Clock::getNanoseconds() const {
	   struct timespec measure;
	   clock_gettime(CLOCK_REALTIME, &measure);
	   return measure.tv_nsec;
   }

   const std::string Clock::getNanosecondsAsString() const {
      std::stringstream parser;
      parser << getNanoseconds();
      return parser.str();
   }

}
