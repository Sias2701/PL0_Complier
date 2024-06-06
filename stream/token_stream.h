#ifndef __PL0_TOKEN_STREAM__
#define __PL0_TOKEN_STREAM__

#include "stream/input_stream.h"
#include "token/token.h"
#include "token/identifier.h"
#include "token/number.h"
#include "token/symbol.h"
#include "token/charstr.h"

#include <memory>

class TokenStream {
private:
    Token _current_token;
    IdentifierParser _id_parser;
    NumberParser _num_parser;
    SymbolParser _sym_parser;
    CharStrParser _cs_parser;
    std::shared_ptr<InputStream> _stream;
    std::stack<Token> _backward;
public:
    TokenStream(std::shared_ptr<InputStream> stream);
    Token get();
    void next();
    void backward(Token token);
};

#endif