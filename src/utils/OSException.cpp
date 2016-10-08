#include "OSException.h"

#include <sstream>
#include <cstring>

OSException::OSException() {
    std::stringstream ss;
    ss << strerror(errno) << " (errno: " << errno << ")";
    errMsg = ss.str();
}

const char *OSException::what() const throw() {
    return errMsg.c_str();
}

OSException::~OSException() throw() {
}
