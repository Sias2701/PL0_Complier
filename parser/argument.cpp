#include "parser/argument.h"

class PLArgumentListParserPrime {
private:
    std::shared_ptr<TokenStream> stream;
public:
    PLArgumentListParserPrime(std::shared_ptr<TokenStream> stream) {
        this->stream = stream;
    }
    std::vector<SemanticToken> parse() {
        Token current_token = this->stream->get();
        std::vector<SemanticToken> ret;
        PLExpressionParser expr_parser(this->stream);
        while (current_token.type == TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) == SymbolType::COMMA)
        {
            this->stream->next();
            SemanticToken expr = expr_parser.parse();
            ret.push_back(expr);
            current_token = this->stream->get();
        }
        return ret;
    }
};

class PLTypedArgumentListParserPrime {
private:
    std::shared_ptr<TokenStream> stream;
public:
    PLTypedArgumentListParserPrime(std::shared_ptr<TokenStream> stream) {
        this->stream = stream;
    }
    std::vector<std::pair<SemanticToken, SemanticToken>> parse() {
    Token current_token = this->stream->get();
    std::vector<std::pair<SemanticToken, SemanticToken>> argument_list;
    SemanticToken type, id;
        while (current_token.type == TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) != SymbolType::COMMA)
        {
            this->stream->next();
            Token type_tok = this->stream->get();
            this->stream->next();
            Token id_tok = this->stream->get();
            this->stream->next();

            if(type_tok.type != TokenType::IDENTIFIER || id_tok.type != TokenType::IDENTIFIER) {
                throw InvalidArgumentTokenException("Token not allowed");
            }

            type.type = SemanticTokenType::IDENTIFIER;
            type.object = type_tok.object;
            id.type = SemanticTokenType::IDENTIFIER;
            id.object = id_tok.object;
            argument_list.push_back(std::make_pair(type, id));
        }

        return argument_list;
    }

};

PLArgumentListParser::PLArgumentListParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
}

SemanticToken PLArgumentListParser::parse() {
    Token current_token = this->stream->get();
    SemanticToken ret;
    std::vector<SemanticToken> argument_list;
    SemanticToken expr;
    PLArgumentListParserPrime prime_parser(this->stream);
    PLExpressionParser expr_parser(this->stream);

    if (current_token.type != TokenType::SYMBOL || std::any_cast<SymbolType>(current_token.object) != SymbolType::RPAR)
    {
        expr = expr_parser.parse();
        argument_list.push_back(expr);

        std::vector<SemanticToken> remained_list = prime_parser.parse();
        std::copy(remained_list.begin(), remained_list.end(), std::back_inserter(argument_list));
    }

    ret.type = SemanticTokenType::ARGUMENT;
    ret.object = std::make_any<std::vector<SemanticToken>>(argument_list);
    return ret;
}

PLTypedArgumentListParser::PLTypedArgumentListParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
}

SemanticToken PLTypedArgumentListParser::parse() {
    Token current_token = this->stream->get();
    SemanticToken ret;
    std::vector<std::pair<SemanticToken, SemanticToken>> argument_list;
    SemanticToken type;
    SemanticToken id;
    PLTypedArgumentListParserPrime prime_parser(this->stream);
    PLExpressionParser expr_parser(this->stream);

    if (current_token.type == TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) != SymbolType::RPAR)
    {
        this->stream->next();
        Token type_tok = this->stream->get();
        this->stream->next();
        Token id_tok = this->stream->get();
        this->stream->next();

        if(type_tok.type != TokenType::IDENTIFIER || id_tok.type != TokenType::IDENTIFIER) {
            throw InvalidArgumentTokenException("Token not allowed");
        }

        type.type = SemanticTokenType::IDENTIFIER;
        type.object = type_tok.object;
        id.type = SemanticTokenType::IDENTIFIER;
        id.object = id_tok.object;

        argument_list.push_back(std::make_pair(type, id));

        std::vector<std::pair<SemanticToken, SemanticToken>> remained_list = prime_parser.parse();
        std::copy(remained_list.begin(), remained_list.end(), std::back_inserter(argument_list));
    }

    ret.type = SemanticTokenType::ARGUMENTDECL;
    ret.object = std::make_any<std::vector<std::pair<SemanticToken, SemanticToken>>>(argument_list);
    return ret;
}

