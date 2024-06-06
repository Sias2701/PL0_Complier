#include "token/symbol.h"

std::ostream& operator<<(std::ostream& os, const SymbolType& symbolType) {
    switch (symbolType) {
        case SymbolType::INVALID:
            os << "INVALID";
            break;
        case SymbolType::SEMICOLON:
            os << "SEMICOLON";
            break;
        case SymbolType::COMMA:
            os << "COMMA";
            break;
        case SymbolType::PLUS:
            os << "PLUS";
            break;
        case SymbolType::DASH:
            os << "DASH";
            break;
        case SymbolType::ASTERISK:
            os << "ASTERISK";
            break;
        case SymbolType::SLASH:
            os << "SLASH";
            break;
        case SymbolType::INC:
            os << "INC";
            break;
        case SymbolType::DEC:
            os << "DEC";
            break;
        case SymbolType::NEG:
            os << "NEG";
            break;
        case SymbolType::LSQUARE:
            os << "LSQUARE";
            break;
        case SymbolType::RSQUARE:
            os << "RSQUARE";
            break;
        case SymbolType::LCURLY:
            os << "LCURLY";
            break;
        case SymbolType::RCURLY:
            os << "RCURLY";
            break;
        case SymbolType::LPAR:
            os << "LPAR";
            break;
        case SymbolType::RPAR:
            os << "RPAR";
            break;
        case SymbolType::PEROID:
            os << "PEROID";
            break;
        case SymbolType::EQ:
            os << "EQ";
            break;
        case SymbolType::NEQ:
            os << "NEQ";
            break;
        case SymbolType::GTR:
            os << "GTR";
            break;
        case SymbolType::LSR:
            os << "LSR";
            break;
        case SymbolType::GEQ:
            os << "GEQ";
            break;
        case SymbolType::LEQ:
            os << "LEQ";
            break;
        case SymbolType::AND:
            os << "AND";
            break;
        case SymbolType::OR:
            os << "OR";
            break;
        case SymbolType::NOT:
            os << "NOT";
            break;
        case SymbolType::ASSIGN:
            os << "ASSIGN";
            break;
        case SymbolType::ADDBY:
            os << "ADDBY";
            break;
        case SymbolType::SUBBY:
            os << "SUBBY";
            break;
        case SymbolType::MULBY:
            os << "MULBY";
            break;
        case SymbolType::DIVBY:
            os << "DIVBY";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}

Token SymbolParser::parse(std::shared_ptr<InputStream> stream) {
    char current_symbol;
    stream->forward();
    Token ret;
    if(stream->_filestream.eof()) {
        ret.type = TokenType::EOT;
        return ret;
    }

    current_symbol = stream->get();
    ret.type = TokenType::SYMBOL;
    
    switch (current_symbol)
    {
        case ';':
            ret.object = std::make_any<SymbolType>(SymbolType::SEMICOLON);
            break;
        case ',':
            ret.object = std::make_any<SymbolType>(SymbolType::COMMA);
            break;
        case '+':
            stream->next();
            current_symbol = stream->get();
            if(current_symbol == '+') {
                ret.object = std::make_any<SymbolType>(SymbolType::INC);
            }
            else {
                stream->backward(current_symbol);

                ret.object = std::make_any<SymbolType>(SymbolType::PLUS);
            }
            break;
        case '-':
            stream->next();
            current_symbol = stream->get();
            if(current_symbol == '-') {
                ret.object = std::make_any<SymbolType>(SymbolType::DEC);
            }
            else {
                if(std::isalnum(current_symbol) || current_symbol == '('){
                    ret.object = std::make_any<SymbolType>(SymbolType::NEG);
                }
                else {
                    ret.object = std::make_any<SymbolType>(SymbolType::DASH);
                }
                stream->backward(current_symbol);
                
            }
            break;
        case '*':
            ret.object = std::make_any<SymbolType>(SymbolType::ASTERISK);
            break;
        case '/':
            ret.object = std::make_any<SymbolType>(SymbolType::SLASH);
            break;
        case '[':
            ret.object = std::make_any<SymbolType>(SymbolType::LSQUARE);
            break;
        case ']':
            ret.object = std::make_any<SymbolType>(SymbolType::RSQUARE);
            break;
        case '(':
            ret.object = std::make_any<SymbolType>(SymbolType::LPAR);
            break;
        case ')':
            ret.object = std::make_any<SymbolType>(SymbolType::RPAR);
            break;
        case '{':
            ret.object = std::make_any<SymbolType>(SymbolType::LCURLY);
            break;
        case '}':
            ret.object = std::make_any<SymbolType>(SymbolType::RCURLY);
            break;
        case '.':
            ret.object = std::make_any<SymbolType>(SymbolType::PEROID);
            break;
        case '=':
            stream->next();
            current_symbol = stream->get();
            if(current_symbol == '=') {
                ret.object = std::make_any<SymbolType>(SymbolType::EQ);
            }
            else {
        
                ret.type = TokenType::INVALID;
            }
            break;
        case '>':
            stream->next();
            current_symbol = stream->get();
            if(current_symbol == '=') {
                ret.object = std::make_any<SymbolType>(SymbolType::GEQ);
            }
            else {
                stream->backward(current_symbol);
                ret.object = std::make_any<SymbolType>(SymbolType::GTR);
            }
            break;
        case '<':
            stream->next();
            current_symbol = stream->get();
            if(current_symbol == '=') {
                ret.object = std::make_any<SymbolType>(SymbolType::LEQ);
            }
            else {
                stream->backward(current_symbol);
                stream->backward(current_symbol);
                ret.object = std::make_any<SymbolType>(SymbolType::LSR);
            }
            break;
        case '&':
            stream->next();
            if(stream->get() == '&') {
                ret.object = std::make_any<SymbolType>(SymbolType::AND);
            }
            else {
                ret.type = TokenType::INVALID;
            }
            break;
        case '|':
            stream->next();
            if(stream->get() == '|') {
                ret.object = std::make_any<SymbolType>(SymbolType::OR);
            }
            else {
                ret.type = TokenType::INVALID;
            }
            break;
        case '!':
            stream->next();
            current_symbol = stream->get();
            if(current_symbol == '=') {
                ret.object = std::make_any<SymbolType>(SymbolType::NEQ);
            }
            else {
                stream->backward(current_symbol);
                stream->backward(current_symbol);
                ret.object = std::make_any<SymbolType>(SymbolType::NOT);
            }
        case ':':
            stream->next();
            current_symbol = stream->get();
            stream->next();
            switch (current_symbol)
            {
                case '+':
                    current_symbol = stream->get();
                    if(current_symbol == '=') {
                    ret.object = std::make_any<SymbolType>(SymbolType::ADDBY);
                    }
                    else {
                        stream->backward(current_symbol);
                        ret.type = TokenType::INVALID;
                    }
                    break;
                case '-':
                    current_symbol = stream->get();
                    if(current_symbol == '=') {
                    ret.object = std::make_any<SymbolType>(SymbolType::SUBBY);
                    }
                    else {
                        stream->backward(current_symbol);
                        ret.type = TokenType::INVALID;
                    }
                    break;
                case '*':
                    current_symbol = stream->get();
                    if(current_symbol == '=') {
                    ret.object = std::make_any<SymbolType>(SymbolType::MULBY);
                    }
                    else {
                        stream->backward(current_symbol);
                        ret.type = TokenType::INVALID;
                    }
                    break;
                case '/':
                    if(stream->get() == '=') {
                    ret.object = std::make_any<SymbolType>(SymbolType::DIVBY);
                    }
                    else {
                        ret.type = TokenType::INVALID;
                    }
                    break;
                case '=':
                    ret.object = std::make_any<SymbolType>(SymbolType::ASSIGN);
                    break;
                default:
                    ret.type = TokenType::INVALID;
                    break;
            }
            break;
        default:
        
            ret.type = TokenType::INVALID;
            break;
    }
    if(ret.type != TokenType::INVALID) {
        stream->next();
    }
    return ret;
}