#ifndef __PL0_TOKEN__
#define __PL0_TOKEN__

#include "stream/input_stream.h"

#include <string>
#include <any>
#include <queue>

enum class TokenType : unsigned char {
    EOT,
    INVALID,
    VOID,
    IDENTIFIER,
    KEYWORD,
    NUMBER,
    OPERATOR,
    SYMBOL,
    CHAR,
    STRING
};

class Token {
public:
    std::any object;
    TokenType type;
};

class AbstractTokenParser {
public:
    virtual Token parse(std::shared_ptr<InputStream> stream) {
        Token ret;
        ret.type = TokenType::VOID;
        return ret;
    };
};

std::ostream& operator<<(std::ostream& os, const TokenType& tokenType);

#endif