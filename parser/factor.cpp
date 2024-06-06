#include "parser/factor.h"

PLFactorParser::PLFactorParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
}

SemanticToken PLFactorParser::parse() {
    PLExpressionParser expr_parser(this->stream);
    PLArgumentListParser args_parser(this->stream);
    PLMemberAccessParser member_access_parser(this->stream);
    Token current_token = this->stream->get();
    SemanticToken ret;
    if(current_token.type == TokenType::EOT) {
        ret.type = SemanticTokenType::EOT;
        return ret;
    }
    if(current_token.type == TokenType::SYMBOL) {
        SemanticToken id;
        switch (std::any_cast<SymbolType>(current_token.object))
        {
            case SymbolType::LPAR: {
                
                this->stream->next();

                SemanticToken expr = expr_parser.parse();
                current_token = this->stream->get();
                if(current_token.type != TokenType::SYMBOL || std::any_cast<SymbolType>(current_token.object) != SymbolType::RPAR) {
                    throw InvalidFactorTokenException("Symbol not allowed");
                }
                ret.type = SemanticTokenType::FACTOR;
                ret.object = std::make_any<SemanticToken>(expr);
                this->stream->next();
                break;
            }
            case SymbolType::INC:{
                SemanticToken warp;
                warp.type = SemanticTokenType::INCBEFORE;
                this->stream->next();
                current_token = this->stream->get();
                if(current_token.type != TokenType::IDENTIFIER) {
                    throw InvalidFactorTokenException("Token not allowed");
                }
                id.type = SemanticTokenType::IDENTIFIER;
                id.object = current_token.object;
                warp.object = std::make_any<SemanticToken>(id);
                ret.type = SemanticTokenType::FACTOR;
                ret.object = std::make_any<SemanticToken>(warp);
                this->stream->next();
                break;
            }
            case SymbolType::DEC: {
                SemanticToken warp;
                
                warp.type = SemanticTokenType::DECBEFORE;
                this->stream->next();
                current_token = this->stream->get();
                if(current_token.type != TokenType::IDENTIFIER) {
                    throw InvalidFactorTokenException("Token not allowed");
                }
                id.type = SemanticTokenType::IDENTIFIER;
                id.object = current_token.object;
                warp.object = std::make_any<SemanticToken>(id);
                ret.type = SemanticTokenType::FACTOR;
                ret.object = std::make_any<SemanticToken>(warp);
                this->stream->next();
                break;
            }
            case SymbolType::NEG: {
                
                this->stream->next();
                current_token = this->stream->get();
                if(current_token.type == TokenType::IDENTIFIER) {
                    SemanticToken warp;
                    id.type = SemanticTokenType::IDENTIFIER;
                    id.object = current_token.object;
                    warp.object = std::make_any<SemanticToken>(id);
                    warp.type = SemanticTokenType::NEG;
                    ret.object = std::make_any<SemanticToken>(warp);
                    ret.type = SemanticTokenType::FACTOR;
                    this->stream->next();
                    return ret;
                } else if(current_token.type == TokenType::NUMBER) {
                    SemanticToken warp;

                    auto obj = std::any_cast<PL0Number>(current_token.object);
                    if(std::holds_alternative<int>(obj)) {     
                        id.type = SemanticTokenType::IMMEDIATE_INTEGER;
                        id.object = ret.object = std::make_any<int>(std::get<int>(obj));
                        warp.object = std::make_any<SemanticToken>(id);
                        warp.type = SemanticTokenType::NEG;
                        ret.object = std::make_any<SemanticToken>(warp);
                        ret.type = SemanticTokenType::FACTOR;
                        this->stream->next();
                        return ret;
                    } else if (std::holds_alternative<float>(obj)) {
                        id.type = SemanticTokenType::IMMEDIATE_FLOAT;
                        id.object = ret.object = std::make_any<float>(std::get<float>(obj));
                        warp.object = std::make_any<SemanticToken>(id);
                        warp.type = SemanticTokenType::NEG;
                        ret.object = std::make_any<SemanticToken>(warp);
                        ret.type = SemanticTokenType::FACTOR;
                        this->stream->next();
                        return ret;
                    }
                } else if(current_token.type == TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) == SymbolType::LPAR){
                    this->stream->next();
                    SemanticToken expr = expr_parser.parse();
                    current_token = this->stream->get();
                    if(current_token.type != TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) != SymbolType::RPAR ) {
                        throw InvalidFactorTokenException("SQUARE not matched");
                    }
                    this->stream->next();
                    SemanticToken warp;
                    warp.object = std::make_any<SemanticToken>(expr);
                    warp.type = SemanticTokenType::NEG;
                    ret.object = std::make_any<SemanticToken>(warp);
                    ret.type = SemanticTokenType::FACTOR;
                    this->stream->next();
                    return ret;
                } else {
                    throw InvalidFactorTokenException("Token not allowed");
                }
                break;
            }
            default:
                throw InvalidFactorTokenException("Symbol not allowed");
        }
        return ret;
    } else if(current_token.type == TokenType::IDENTIFIER) {
        SemanticToken id;
        id.type = SemanticTokenType::IDENTIFIER;
        id.object = current_token.object;
        this->stream->next();
        current_token = this->stream->get();
        if(current_token.type == TokenType::SYMBOL) {
            switch (std::any_cast<SymbolType>(current_token.object))
            {
                case SymbolType::LPAR: {
                    this->stream->next();
                    ret.type = SemanticTokenType::FACTOR;
                    SemanticToken args = args_parser.parse();
                    if(args.type != SemanticTokenType::ARGUMENT) {
                        throw InvalidFactorTokenException("Token not allowed");
                    }
                    current_token = this->stream->get();
                    if(current_token.type != TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) != SymbolType::RPAR ) {
                        throw InvalidFactorTokenException("PAR not matched");
                    }
                    this->stream->next();

                    FuncionCallSemantic ctx;
                    ctx.funcion_name = std::any_cast<std::string>(id.object);
                    ctx.argument_list = std::any_cast<std::vector<SemanticToken>>(args.object);
                    SemanticToken warp;
                    warp.type = SemanticTokenType::FUNCTION_CALL;
                    warp.object = std::make_any<FuncionCallSemantic>(ctx);
                    ret.object = std::make_any<SemanticToken>(warp);
                    return ret;
                }

                case SymbolType::PEROID: {
                    ret.type = SemanticTokenType::FACTOR;
                    this->stream->next();
                    SemanticToken access = member_access_parser.parse();                    
                    
                    if(access.type != SemanticTokenType::MEMBER_ACCESS) {
                        throw InvalidFactorTokenException("Token not allowed");
                    }
                    SemanticToken warp;
                    warp.type = SemanticTokenType::MEMBER_ACCESS;
                    warp.object = std::make_any<std::pair<SemanticToken, SemanticToken>>(std::make_pair(id, access));
                    ret.object = std::make_any<SemanticToken>(warp);
                    return ret;
                }

                case SymbolType::LSQUARE: {
                    ret.type = SemanticTokenType::FACTOR;
                    this->stream->next();
                    ArrayAccessSemantic ctx;
                    SemanticToken expr = expr_parser.parse();
                    if(expr.type != SemanticTokenType::EXPRESSION) {
                        throw InvalidFactorTokenException("Token not allowed");
                    }
                    current_token = this->stream->get();
                    if(current_token.type != TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) != SymbolType::RSQUARE ) {
                        throw InvalidFactorTokenException("SQUARE not matched");
                    }
                    this->stream->next();

                    ctx.action.type = SemanticTokenType::VOID;
                    ctx.offset = expr;
                    SemanticToken warp;
                    warp.type = SemanticTokenType::ARRAY_ACCESS;
                    warp.object = std::make_any<ArrayAccessSemantic>(ctx);
                    ret.object = std::make_any<SemanticToken>(warp);
                    return ret;
                }
                
                case SymbolType::INC: {
                    ret.type = SemanticTokenType::FACTOR;
                    this->stream->next();
                    SemanticToken warp;
                    warp.type = SemanticTokenType::INCAFTER;
                    warp.object = std::make_any<SemanticToken>(id);
                    ret.object = std::make_any<SemanticToken>(warp);
                    return ret;
                    break;
                }
                case SymbolType::DEC: {
                    ret.type = SemanticTokenType::FACTOR;
                    this->stream->next();
                    SemanticToken warp;
                    warp.type = SemanticTokenType::DECAFTER;
                    warp.object = std::make_any<SemanticToken>(id);
                    ret.object = std::make_any<SemanticToken>(warp);
                    return ret;
                    break;
                }
                default:
                    ret.type = SemanticTokenType::FACTOR;
                    ret.object = std::make_any<SemanticToken>(id);
                    return ret;
            }
        } else {
            ret.type = SemanticTokenType::FACTOR;
            ret.object = std::make_any<SemanticToken>(id);
            return ret;
        }
    } else if(current_token.type == TokenType::CHAR) {
        SemanticToken warp;
        warp.type = SemanticTokenType::IMMEDIATE_CHAR;
        warp.object = std::make_any<char>(std::any_cast<std::string>(current_token.object)[1]);
        ret.object = std::make_any<SemanticToken>(warp);
        ret.type = SemanticTokenType::FACTOR;
        this->stream->next();
        return ret;
    } else if(current_token.type == TokenType::STRING) {
        std::string current_str = std::any_cast<std::string>(current_token.object);
        SemanticToken warp;
        warp.type = SemanticTokenType::IMMEDIATE_STRING;
        warp.object = std::make_any<std::string>(current_str.substr(1, current_str.length() - 2));
        ret.object = std::make_any<SemanticToken>(warp);
        ret.type = SemanticTokenType::FACTOR;
        this->stream->next();
        return ret;
    } else if(current_token.type == TokenType::NUMBER) {
        auto num = std::any_cast<PL0Number>(current_token.object);
        if(std::holds_alternative<int>(num)) {
            SemanticToken warp;
            warp.type = SemanticTokenType::IMMEDIATE_INTEGER;
            warp.object = std::make_any<int>(std::get<int>(num));
            ret.object = std::make_any<SemanticToken>(warp);
            ret.type = SemanticTokenType::FACTOR;
        } else if (std::holds_alternative<float>(num)) {

            SemanticToken warp;
            warp.type = SemanticTokenType::IMMEDIATE_FLOAT;
            warp.object = std::make_any<float>(std::get<float>(num));
            ret.object = std::make_any<SemanticToken>(warp);
            ret.type = SemanticTokenType::FACTOR;
        }
        this->stream->next();
        return ret;
    } else {
        ret.type = SemanticTokenType::VOID;
        return ret;
    }
}

PLMemberAccessParser::PLMemberAccessParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
}

SemanticToken PLMemberAccessParser::parse() {
    Token current_token = this->stream->get();
    PLExpressionParser expr_parser(this->stream);
    
    SemanticToken ret;
    if(current_token.type == TokenType::EOT) {
        ret.type = SemanticTokenType::EOT;
        return ret;
    }

    if(current_token.type != TokenType::IDENTIFIER) {
        throw "Invalid Token";
    }

    SemanticToken member;

    member.object = current_token.object;
    member.type = SemanticTokenType::IDENTIFIER;
    this->stream->next();

    current_token = this->stream->get();

    if(current_token.type == TokenType::SYMBOL) {
        switch (std::any_cast<SymbolType>(current_token.object))
        {
            case SymbolType::LSQUARE: {
                this->stream->next();
                SemanticToken expr = expr_parser.parse();
                ArrayAccessSemantic ctx;
                current_token = this->stream->get();
                if(current_token.type != TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) != SymbolType::LSQUARE ) {
                    throw InvalidFactorTokenException("SQUARE not matched");
                }
                this->stream->next();
                current_token = this->stream->get();
                if(current_token.type == TokenType::SYMBOL && std::any_cast<SymbolType>(current_token.object) == SymbolType::PEROID ) {
                    this->stream->next();
                    SemanticToken access = this->parse();
                    if(access.type != SemanticTokenType::MEMBER_ACCESS) {
                        throw InvalidFactorTokenException("Token not allowed");
                    }
                    MemberAccessSemantic sematic;
                    sematic.member = member;
                    sematic.action = access;
                    ctx.action.type = SemanticTokenType::MEMBER_ACCESS;
                    ctx.action.object = std::make_any<MemberAccessSemantic>(sematic);
                    ctx.offset = expr;
                    SemanticToken warp;
                    warp.type = SemanticTokenType::ARRAY_ACCESS;
                    warp.object = std::make_any<ArrayAccessSemantic>(ctx);
                    MemberAccessSemantic ctx1;
                    ctx1.action = warp;
                    ctx1.member = member;
                    ret.type = SemanticTokenType::MEMBER_ACCESS;
                    ret.object = std::make_any<MemberAccessSemantic>(ctx1);
                    return ret;
                }
                SemanticToken warp;
                ctx.action.type = SemanticTokenType::VOID;
                ctx.offset = expr;
                warp.type = SemanticTokenType::ARRAY_ACCESS;
                warp.object = std::make_any<ArrayAccessSemantic>(ctx);
                MemberAccessSemantic ctx1;
                ctx1.action = warp;
                ctx1.member = member;
                ret.type = SemanticTokenType::MEMBER_ACCESS;
                ret.object = std::make_any<MemberAccessSemantic>(ctx1);
                return ret;
            }
            break;
            case SymbolType::PEROID: {
                SemanticToken access = this->parse();
                    
                if(access.type != SemanticTokenType::MEMBER_ACCESS) {
                    throw InvalidFactorTokenException("Token not allowed");
                }
                SemanticToken warp;
                warp.type = SemanticTokenType::MEMBER_ACCESS;
                MemberAccessSemantic sematic;
                sematic.member = member;
                sematic.action = access;
                warp.object = std::make_any<MemberAccessSemantic>(sematic);
                ret.object = std::make_any<SemanticToken>(warp);
                ret.type = SemanticTokenType::MEMBER_ACCESS;
                return ret;
            }
                break;

            default:
            {
                ret.type = SemanticTokenType::MEMBER_ACCESS;
                MemberAccessSemantic sematic;
                sematic.action.type = SemanticTokenType::VOID;
                sematic.member = member;
                ret.object = std::make_any<MemberAccessSemantic>(member);
                return ret;
            }
            break;
        }
    } else {
        throw InvalidFactorTokenException("Token not allowed");
    }
}