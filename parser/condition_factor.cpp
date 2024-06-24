#include "parser/condition_factor.h"

PLConditionFactorParser::PLConditionFactorParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
    this->suffix_stack = std::make_shared<std::vector<SemanticToken>>();
    this->operator_stack = std::make_shared<std::stack<SemanticToken>>();
}

SemanticToken PLConditionFactorParser::parse() {
    Token current_token = this->stream->get();
    PLExpressionParser expr_parser(this->stream);

    SemanticToken ret;
    if(current_token.type == TokenType::EOT) {
        ret.type = SemanticTokenType::EOT;
        return ret;
    }
    if(current_token.type == TokenType::KEYWORD && std::any_cast<std::string>(current_token.object) == "odd") {
        this->stream->next();
        SemanticToken expr = expr_parser.parse();
        if(expr.type != SemanticTokenType::EXPRESSION) {
            throw InvalidExpressionTokenException("[stynax error] : invalid expression");
        }
        SemanticToken warp;
        warp.object = std::make_any<SemanticToken>(expr);
        warp.type = SemanticTokenType::ODD;
        this->suffix_stack->push_back(warp);
        ret.type = SemanticTokenType::CONDITION_FACTOR;
        ret.object = std::make_any<SemanticToken>(warp);
    }
    SemanticToken op1 = expr_parser.parse();
    if(op1.type != SemanticTokenType::EXPRESSION) {
        throw InvalidConditionTokenException("Token not allowed");
    }
    SemanticToken op2;
    SemanticToken op;
    current_token = this->stream->get();
    if(current_token.type != TokenType::SYMBOL) {
        throw InvalidConditionTokenException("Symbol not allowed");
    }
    this->suffix_stack->push_back(op1);
    switch (std::any_cast<SymbolType>(current_token.object))
    {
        case SymbolType::EQ:
            op.type = SemanticTokenType::EQ;
            this->operator_stack->push(op);
            break;
        case SymbolType::NEQ:
            op.type = SemanticTokenType::NEG;
            this->operator_stack->push(op);
            break;
        case SymbolType::GTR:
            op.type = SemanticTokenType::GT;
            this->operator_stack->push(op);
            break;
        case SymbolType::GEQ:
            op.type = SemanticTokenType::GEQ;
            this->operator_stack->push(op);
            break;
        case SymbolType::LSR:
            op.type = SemanticTokenType::LT;
            this->operator_stack->push(op);
            break;
        case SymbolType::LEQ:
            op.type = SemanticTokenType::LEQ;
            this->operator_stack->push(op);
            break;

        default:
            break;
    }
    this->stream->next();
    op2 = expr_parser.parse();
    if(op2.type != SemanticTokenType::EXPRESSION) {
        throw InvalidConditionTokenException("Token not allowed");
    }
    this->suffix_stack->push_back(op2);

    while (!this->operator_stack->empty())
    {  
        this->suffix_stack->push_back(this->operator_stack->top());
        this->operator_stack->pop();
    }
    ret.type = SemanticTokenType::CONDITION_FACTOR;
    ret.object = std::make_any<std::vector<SemanticToken>>(*this->suffix_stack);
    this->suffix_stack = std::make_shared<std::vector<SemanticToken>>();
    return ret;
}