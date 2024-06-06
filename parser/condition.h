#ifndef __PL0_CONDITION__
#define __PL0_CONDITION__

#include "parser/parser.h"
#include "parser/condition_term.h"

class InvalidConditionTokenException : std::exception {
private:
    std::string message;
public:
    InvalidConditionTokenException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class PLConditionParser : virtual public PLIntermediateParser{
    std::shared_ptr<std::stack<SemanticToken>> suffix_stack;
    std::shared_ptr<std::stack<SemanticToken>> operator_stack;
public:
    PLConditionParser(std::shared_ptr<TokenStream> stream);
    SemanticToken parse();
};



#endif