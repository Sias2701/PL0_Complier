#ifndef __PL0_STATEMENT__
#define __PL0_STATEMENT__

#include "stream/token_stream.h"

#include <any>

enum class PLStatementAction : unsigned char{
    EXPRESSION,
    CONSTDECLARE,
    VARDECLARE,
    STRUCTDECLARE,
    TYPEDECLARE,
    FUNCDECLARE,
    IFELSE,
    FORLOOP,
    WHILELOOP,
    DOWHILELOOP,
    ASSIGN
};

struct PLStatement {
    PLStatementAction action;
    size_t index;
    std::any statement_body;
};

class PLStatementParser {
private:
    std::shared_ptr<TokenStream> stream;
public:
    PLStatementParser(std::shared_ptr<TokenStream> stream);
    PLStatement parse();
};
#endif