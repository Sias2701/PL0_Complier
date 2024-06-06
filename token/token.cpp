#include "token.h"

std::ostream& operator<<(std::ostream& os, const TokenType& tokenType) {
    switch (tokenType) {
        case TokenType::EOT:
            os << "EOT";
            break;
        case TokenType::INVALID:
            os << "INVALID";
            break;
        case TokenType::VOID:
            os << "VOID";
            break;
        case TokenType::IDENTIFIER:
            os << "IDENTIFIER";
            break;
        case TokenType::KEYWORD:
            os << "KEYWORD";
            break;
        case TokenType::NUMBER:
            os << "NUMBER";
            break;
        case TokenType::SYMBOL:
            os << "SYMBOL";
            break;
        case TokenType::CHAR:
            os << "CHAR";
            break;
        case TokenType::STRING:
            os << "STRING";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}