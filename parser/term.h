#ifndef __PL0_TERM__
#define __PL0_TERM__

#include "parser/parser.h"
#include "parser/factor.h"

#include <exception>
#include <variant>

class InvalidTermTokenException : std::exception {
private:
    std::string message;
public:
    InvalidTermTokenException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class PLTermParser : virtual public PLIntermediateParser{
private:
    std::shared_ptr<std::vector<SemanticToken>> suffix_stack;
    std::shared_ptr<std::stack<SemanticToken>> operator_stack;
public:
    PLTermParser(std::shared_ptr<TokenStream> stream);
    SemanticToken parse();
};

bool is_valid_factor(SemanticToken &token);

#endif