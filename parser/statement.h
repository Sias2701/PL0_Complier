#ifndef __PL0_STATEMENT__
#define __PL0_STATEMENT__

#include <any>

enum class PLStatementAction : unsigned char {
    INVALID,
    VOID,
    EOS,
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
};

struct PLStatementBlock {
    std::vector<PLStatement> blocks;
};

#endif