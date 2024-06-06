#include "parser/condition.h"

class PLConditionParserPrime : virtual public PLIntermediateParser{

public:
    PLConditionParserPrime(std::shared_ptr<TokenStream> stream) {
        this->stream = stream;
    };
    SemanticToken parse(std::shared_ptr<std::stack<SemanticToken>> suffix_stack, std::shared_ptr<std::stack<SemanticToken>> operator_stack) {
        Token current_token = this->stream->get();
        SemanticToken ret;
        PLConditionTermParser term_parser(this->stream);
        if(current_token.type == TokenType::EOT) {
            ret.type = SemanticTokenType::EOT;
            return ret;
        }
        Token op_tok;
        while (current_token.type == TokenType::SYMBOL && (std::any_cast<SymbolType>(current_token.object) == SymbolType::AND || std::any_cast<SymbolType>(current_token.object) == SymbolType::OR)) {
            op_tok = current_token;
            this->stream->next();

            SemanticToken term = term_parser.parse();
            
            if(term.type != SemanticTokenType::CONDITION_TERM) {
                throw InvalidExpressionTokenException("Token not allowed");
            }

            suffix_stack->push(term);
            if(std::any_cast<SymbolType>(op_tok.object) == SymbolType::OR) {
                SemanticToken op;
                op.type = SemanticTokenType::AND;
                operator_stack->push(op);
            } else if(std::any_cast<SymbolType>(op_tok.object) == SymbolType::AND) {
                SemanticToken op;
                op.type = SemanticTokenType::OR;
                operator_stack->push(op);
            }
            current_token = this->stream->get();
        }
        ret.type = SemanticTokenType::VOID;

        return ret;
    }
};

PLConditionParser::PLConditionParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
    this->suffix_stack = std::make_shared<std::stack<SemanticToken>>();
    this->operator_stack = std::make_shared<std::stack<SemanticToken>>();
}

SemanticToken PLConditionParser::parse() {
    Token current_token = this->stream->get();
    PLConditionTermParser term_parser(this->stream);
    PLConditionParserPrime prime_parser(this->stream);
    PLExpressionParser expr_parser(this->stream);
    SemanticToken ret;
    if(current_token.type == TokenType::EOT) {
        ret.type = SemanticTokenType::EOT;
        return ret;
    }

    SemanticToken term = term_parser.parse();
    if(term.type != SemanticTokenType::CONDITION_TERM) {
        throw InvalidExpressionTokenException("Token not allowed");
    }

    this->suffix_stack->push(term);

    SemanticToken result = prime_parser.parse(this->suffix_stack, this->operator_stack);

    if(result.type != SemanticTokenType::VOID) {
        throw InvalidExpressionTokenException("[stynax error] : invalid expression");
    }

    while (!this->operator_stack->empty())
    {  
        this->suffix_stack->push(this->operator_stack->top());
        this->operator_stack->pop();
    }
    
    ret.type = SemanticTokenType::CONDITION;
    ret.object = std::make_shared<std::stack<SemanticToken>>(*this->suffix_stack);
    this->suffix_stack = std::make_shared<std::stack<SemanticToken>>();
    return ret;
}
