#ifndef OSEXCEPTION_H_
#define OSEXCEPTION_H_

#include <exception>
#include <string>

class OSException : public std::exception {
private:
    std::string errMsg;
public:
    OSException();
    virtual const char *what() const throw();
    virtual ~OSException() throw();
};

#endif
