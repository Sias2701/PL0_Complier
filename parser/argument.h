#ifndef __PL0_ARGUMENTS__
#define __PL0_ARGUMENTS__

#include "parser/parser.h"
#include "parser/expression.h"


class PLArgumentListParser : virtual public PLIntermediateParser{
public:
    PLArgumentListParser(std::shared_ptr<TokenStream> stream);
    SemanticToken parse();
};

class PLTypedArgumentListParser : virtual public PLIntermediateParser{
public:
    PLTypedArgumentListParser(std::shared_ptr<TokenStream> stream);
    SemanticToken parse();
};

class InvalidArgumentTokenException : std::exception {
private:
    std::string message;
public:
    InvalidArgumentTokenException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif