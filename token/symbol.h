#ifndef __PL0_SYMBOL_TOKEN__
#define __PL0_SYMBOL_TOKEN__

#include "stream/input_stream.h"
#include "token/token.h"

enum class SymbolType : unsigned char {
    INVALID,
    SEMICOLON,
    COMMA,
    PLUS,
    DASH,
    ASTERISK,
    SLASH,
    INC,
    DEC,
    NEG,
    LSQUARE,
    RSQUARE,
    LCURLY,
    RCURLY,
    LPAR,
    RPAR,
    PEROID,
    EQ,
    NEQ,
    GTR,
    LSR,
    GEQ,
    LEQ,
    AND,
    OR,
    NOT,
    ASSIGN,
    ADDBY,
    SUBBY,
    MULBY,
    DIVBY,
};

std::ostream& operator<<(std::ostream& os, const SymbolType& symbolType);


class SymbolParser final : virtual public AbstractTokenParser{
public:
    Token parse(std::shared_ptr<InputStream> stream);
};

#endif