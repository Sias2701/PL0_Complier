#ifndef __PL0_FACTOR__
#define __PL0_FACTOR__

#include "parser/parser.h"
#include "parser/argument.h"
#include "parser/expression.h"
#include "parser/member_access.h"

#include <exception>
#include <variant>

class InvalidFactorTokenException : std::exception {
private:
    std::string message;
public:
    InvalidFactorTokenException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class PLFactorParser : virtual public PLIntermediateParser{
public:
    PLFactorParser(std::shared_ptr<TokenStream> stream);
    SemanticToken parse();
};

class PLMemberAccessParser : virtual public PLIntermediateParser {
public:
    PLMemberAccessParser(std::shared_ptr<TokenStream> stream);
    SemanticToken parse();
};

struct ArrayAccessSemantic {
    SemanticToken offset;
    SemanticToken action;
};

struct MemberAccessSemantic {
    SemanticToken member;
    SemanticToken action;
};
#endif