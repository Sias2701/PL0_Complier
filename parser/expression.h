#ifndef __PL0_EXPRESSION__
#define __PL0_EXPRESSION__

#include "parser/parser.h"
#include "parser/term.h"

class InvalidExpressionTokenException : std::exception {
private:
    std::string message;
public:
    InvalidExpressionTokenException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class PLExpressionParser : virtual public PLIntermediateParser{
    std::shared_ptr<std::vector<SemanticToken>> suffix_stack;
    std::shared_ptr<std::stack<SemanticToken>> operator_stack;
public:
    PLExpressionParser(std::shared_ptr<TokenStream> stream);
    SemanticToken parse();
};

#endif