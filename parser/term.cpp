#include "parser/term.h"

bool is_valid_factor(SemanticToken &token) {
    switch (token.type)
    {
        case SemanticTokenType::IMMEDIATE_CHAR:
        case SemanticTokenType::IMMEDIATE_FLOAT:
        case SemanticTokenType::IMMEDIATE_INTEGER:
        case SemanticTokenType::IDENTIFIER:
        case SemanticTokenType::FUNCTION_CALL:
        case SemanticTokenType::ARRAY_ACCESS:
        case SemanticTokenType::MEMBER_ACCESS:
        case SemanticTokenType::INCBEFORE:
        case SemanticTokenType::INCAFTER:
        case SemanticTokenType::DECBEFORE:
        case SemanticTokenType::DECAFTER:
            return true;
            break;

        default:
            return false;
            break;
    }
}

class PLTermParserPrime {
private:
    std::shared_ptr<TokenStream> stream;
public:
    PLTermParserPrime(std::shared_ptr<TokenStream> stream) {
        this->stream = stream;
    }
    SemanticToken parse(std::shared_ptr<std::vector<SemanticToken>> suffix_stack, std::shared_ptr<std::stack<SemanticToken>> operator_stack) {
        Token current_token = this->stream->get();
        PLFactorParser factor_parser(this->stream);
        SemanticToken ret;
        if(current_token.type == TokenType::EOT) {
            ret.type = SemanticTokenType::EOT;
            return ret;
        }
        while (current_token.type == TokenType::SYMBOL && (std::any_cast<SymbolType>(current_token.object) == SymbolType::ASTERISK || std::any_cast<SymbolType>(current_token.object) == SymbolType::SLASH)) {
            this->stream->next();

            SemanticToken factor = factor_parser.parse();
            
            if(factor.type != SemanticTokenType::FACTOR) {
                throw InvalidTermTokenException("Token not allowed");
            }

            suffix_stack->push_back(factor);
            if(std::any_cast<SymbolType>(current_token.object) == SymbolType::ASTERISK) {
                SemanticToken op;
                op.type = SemanticTokenType::MUL;
                operator_stack->push(op);
            } else if(std::any_cast<SymbolType>(current_token.object) == SymbolType::SLASH) {
                SemanticToken op;
                op.type = SemanticTokenType::DIV;
                operator_stack->push(op);
            }
            current_token = this->stream->get();
        }
        ret.type = SemanticTokenType::VOID;
        return ret;
    }
};

PLTermParser::PLTermParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
    this->suffix_stack = std::make_shared<std::vector<SemanticToken>>();
    this->operator_stack = std::make_shared<std::stack<SemanticToken>>();
}

SemanticToken PLTermParser::parse() {
    PLFactorParser factor_parser(this->stream);
    PLTermParserPrime prime_parser(this->stream);
    Token current_token = this->stream->get();
    SemanticToken ret;

    if(current_token.type == TokenType::EOT) {
        ret.type = SemanticTokenType::EOT;
        return ret;
    }

    SemanticToken factor = factor_parser.parse();
    if(factor.type != SemanticTokenType::FACTOR) {
        throw InvalidTermTokenException("Token not allowed");
    }

    this->suffix_stack->push_back(factor);

    SemanticToken result = prime_parser.parse(this->suffix_stack, this->operator_stack);
    if(result.type != SemanticTokenType::VOID) {
        throw InvalidTermTokenException("Token not allowed");
    }

    while (this->operator_stack->empty() == false)
    {
        this->suffix_stack->push_back(this->operator_stack->top());
        this->operator_stack->pop();
    }
    ret.type = SemanticTokenType::TERM;
    ret.object = std::make_any<std::vector<SemanticToken>>(*this->suffix_stack);
    this->suffix_stack = std::make_shared<std::vector<SemanticToken>>();
    return ret;
}