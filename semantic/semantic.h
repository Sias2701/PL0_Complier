#ifndef __PL0_SEMANTIC__
#define __PL0_SEMANTIC__

#include <any>
#include <string>
#include <vector>

enum class SemanticTokenType {
    INVALID,
    VOID,
    EOT,
    EOE,
    OPERAND,
    EQ,
    NEQ,
    GEQ,
    LEQ,
    LT,
    GT,
    NEG,
    LPAR,
    RPAR,
    IDENTIFIER,
    ARRAY_ACCESS,
    MEMBER_ACCESS,
    MEMBER_ACCESS_ACTION,
    FUNCTION_CALL,
    ARGUMENT,
    ARGUMENTDECL,
    TERM,
    FACTOR,
    EXPRESSION,
    IMMEDIATE_CHAR,
    IMMEDIATE_INTEGER,
    IMMEDIATE_STRING,
    IMMEDIATE_FLOAT,
    INCBEFORE,
    INCAFTER,
    DECBEFORE,
    DECAFTER,
    ADD,
    SUB,
    MUL,
    DIV,
    CONDITION_FACTOR,
    CONDITION_TERM,
    CONDITION,
    NOT,
    AND,
    OR,
    ODD
};

struct SemanticToken {
    SemanticTokenType type;
    std::any object;
};

struct FuncionCallSemantic {
    std::string funcion_name;
    std::vector<SemanticToken> argument_list;
};

#endif