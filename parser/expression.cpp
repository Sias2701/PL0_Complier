#include "parser/expression.h"

class PLExpressionParserPrime {
private:
    std::shared_ptr<TokenStream> stream;
public:
    PLExpressionParserPrime(std::shared_ptr<TokenStream> stream) {
        this->stream = stream;
    }
    SemanticToken parse(std::shared_ptr<std::vector<SemanticToken>> suffix_stack, std::shared_ptr<std::stack<SemanticToken>> operator_stack) {
        Token current_token = this->stream->get();
        SemanticToken ret;
        PLTermParser term_parser(this->stream);
        if(current_token.type == TokenType::EOT) {
            ret.type = SemanticTokenType::EOT;
            return ret;
        }
        Token op_tok;
        while (current_token.type == TokenType::SYMBOL && (std::any_cast<SymbolType>(current_token.object) == SymbolType::PLUS || std::any_cast<SymbolType>(current_token.object) == SymbolType::DASH)) {
            op_tok = current_token;
            this->stream->next();

            SemanticToken term = term_parser.parse();
            
            if(term.type != SemanticTokenType::TERM) {
                throw InvalidExpressionTokenException("Token not allowed");
            }

            suffix_stack->push_back(term);
            if(std::any_cast<SymbolType>(op_tok.object) == SymbolType::PLUS) {
                SemanticToken op;
                op.type = SemanticTokenType::ADD;
                operator_stack->push(op);
            } else if(std::any_cast<SymbolType>(op_tok.object) == SymbolType::DASH) {
                SemanticToken op;
                op.type = SemanticTokenType::SUB;
                operator_stack->push(op);
            }
            current_token = this->stream->get();
        }
        ret.type = SemanticTokenType::VOID;
        return ret;
    }
};

PLExpressionParser::PLExpressionParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
    this->suffix_stack = std::make_shared<std::vector<SemanticToken>>();
    this->operator_stack = std::make_shared<std::stack<SemanticToken>>();
}

SemanticToken PLExpressionParser::parse() {
    Token current_token = this->stream->get();
    PLTermParser term_parser(this->stream);
    PLExpressionParserPrime prime_parser(this->stream);

    SemanticToken ret;
    if(current_token.type == TokenType::EOT) {
        ret.type = SemanticTokenType::EOT;
        return ret;
    }

    if(current_token.type == TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) == SymbolType::SEMICOLON) {
        ret.type = SemanticTokenType::EXPRESSION;
        ret.object = std::make_any<std::vector<SemanticToken>>(*this->suffix_stack);
        return ret;
    }

    SemanticToken term = term_parser.parse();
    if(term.type != SemanticTokenType::TERM) {
        throw InvalidExpressionTokenException("Token not allowed");
    }

    this->suffix_stack->push_back(term);

    SemanticToken result = prime_parser.parse(this->suffix_stack, this->operator_stack);

    if(result.type != SemanticTokenType::VOID) {
        throw InvalidExpressionTokenException("[stynax error] : invalid expression");
    }

    while (!this->operator_stack->empty())
    {  
        this->suffix_stack->push_back(this->operator_stack->top());
        this->operator_stack->pop();
    }
    
    ret.type = SemanticTokenType::EXPRESSION;
    ret.object = std::make_any<std::vector<SemanticToken>>(*this->suffix_stack);
    this->suffix_stack = std::make_shared<std::vector<SemanticToken>>();
    return ret;
}