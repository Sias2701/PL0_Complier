#include "parser/condition_term.h"

PLConditionTermParser::PLConditionTermParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
}

SemanticToken PLConditionTermParser::parse() {
    Token current_token = this->stream->get();
    PLConditionFactorParser factor_parser(this->stream);
    PLConditionParser cond_parser(this->stream);
    SemanticToken ret;
    if(current_token.type == TokenType::EOT) {
        ret.type = SemanticTokenType::EOT;
        return ret;
    }
    
    if(current_token.type == TokenType::SYMBOL) {
        switch (std::any_cast<SymbolType>(current_token.object))
        {
            case SymbolType::LPAR: {
                this->stream->next();
                SemanticToken cond = cond_parser.parse();
                if(cond.type != SemanticTokenType::CONDITION) {
                    throw InvalidConditionTokenException("Token not allowed");
                }
                current_token = this->stream->get();
                if(current_token.type != TokenType::SYMBOL || std::any_cast<SymbolType>(current_token.object) != SymbolType::RPAR) {
                    throw InvalidFactorTokenException("Symbol not allowed");
                }
                ret.type = SemanticTokenType::CONDITION_TERM;
                ret.object = std::make_any<SemanticToken>(cond);
                this->stream->next();
            }

            case SymbolType::NOT: {
                this->stream->next();
                SemanticToken term = this->parse();
                if(term.type != SemanticTokenType::CONDITION_TERM) {
                    throw InvalidConditionTokenException("Token not allowed");
                }
                SemanticToken warp;
                warp.type = SemanticTokenType::NOT;
                warp.object = std::make_any<SemanticToken>(term);

                ret.type = SemanticTokenType::CONDITION_TERM;
                ret.object = std::make_any<SemanticToken>(warp);
                this->stream->next();
            }
            default:
                throw InvalidConditionTokenException("Symbol not allowed");
        }
        return ret;
    } else {
        SemanticToken factor = factor_parser.parse();
        ret.type = SemanticTokenType::CONDITION_TERM;
        ret.object = std::make_any<SemanticToken>(factor);
    }

    return ret;
}