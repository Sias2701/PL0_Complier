#ifndef __PL0_RUNTIME__
#define __PL0_RUNTIME__

#include <exception>
#include <string>

class RuntimeError : std::exception {
private:
    std::string message;
public:
    RuntimeError(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif