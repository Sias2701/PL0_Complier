#include "token/identifier.h"

IdentifierParser::IdentifierParser() {
    this->alphabet = {
        'a', 'b', 'c', 'd', 'e', 
        'f', 'g', 'h', 'i', 'j', 
        'k', 'l', 'm', 'n', 'o', 
        'p', 'q', 'r', 's', 't', 
        'u', 'v', 'w', 'x', 'y', 
        'z', 'A', 'B', 'C', 'D', 
        'E', 'F', 'G', 'H', 'I', 
        'J', 'K', 'L', 'M', 'N', 
        'O', 'P', 'Q', 'R', 'S', 
        'T', 'U', 'V', 'W', 'X', 
        'Y', 'Z', '0', '1', '2', 
        '3', '4', '5', '6', '7', 
        '8', '9', '_'
    };

    this->first = {
        'a', 'b', 'c', 'd', 'e', 
        'f', 'g', 'h', 'i', 'j', 
        'k', 'l', 'm', 'n', 'o', 
        'p', 'q', 'r', 's', 't', 
        'u', 'v', 'w', 'x', 'y', 
        'z', 'A', 'B', 'C', 'D', 
        'E', 'F', 'G', 'H', 'I', 
        'J', 'K', 'L', 'M', 'N', 'O', 
        'P', 'Q', 'R', 'S', 'T', 'U', 
        'V', 'W', 'X', 'Y', 'Z', '_'

    };

    this->states = {
        1,2
    };

    this->accept_states = {
        2
    };

    this->_add_transition(1, 'a', 2);
    this->_add_transition(1, 'b', 2);
    this->_add_transition(1, 'c', 2);
    this->_add_transition(1, 'd', 2);
    this->_add_transition(1, 'e', 2);
    this->_add_transition(1, 'f', 2);
    this->_add_transition(1, 'g', 2);
    this->_add_transition(1, 'h', 2);
    this->_add_transition(1, 'i', 2);
    this->_add_transition(1, 'j', 2);
    this->_add_transition(1, 'k', 2);
    this->_add_transition(1, 'l', 2);
    this->_add_transition(1, 'm', 2);
    this->_add_transition(1, 'n', 2);
    this->_add_transition(1, 'o', 2);
    this->_add_transition(1, 'p', 2);
    this->_add_transition(1, 'q', 2);
    this->_add_transition(1, 'r', 2);
    this->_add_transition(1, 's', 2);
    this->_add_transition(1, 't', 2);
    this->_add_transition(1, 'u', 2);
    this->_add_transition(1, 'v', 2);
    this->_add_transition(1, 'w', 2);
    this->_add_transition(1, 'x', 2);
    this->_add_transition(1, 'y', 2);
    this->_add_transition(1, 'z', 2);
    this->_add_transition(1, 'A', 2);
    this->_add_transition(1, 'B', 2);
    this->_add_transition(1, 'C', 2);
    this->_add_transition(1, 'D', 2);
    this->_add_transition(1, 'E', 2);
    this->_add_transition(1, 'F', 2);
    this->_add_transition(1, 'G', 2);
    this->_add_transition(1, 'H', 2);
    this->_add_transition(1, 'I', 2);
    this->_add_transition(1, 'J', 2);
    this->_add_transition(1, 'K', 2);
    this->_add_transition(1, 'L', 2);
    this->_add_transition(1, 'M', 2);
    this->_add_transition(1, 'N', 2);
    this->_add_transition(1, 'O', 2);
    this->_add_transition(1, 'P', 2);
    this->_add_transition(1, 'Q', 2);
    this->_add_transition(1, 'R', 2);
    this->_add_transition(1, 'S', 2);
    this->_add_transition(1, 'T', 2);
    this->_add_transition(1, 'U', 2);
    this->_add_transition(1, 'V', 2);
    this->_add_transition(1, 'W', 2);
    this->_add_transition(1, 'X', 2);
    this->_add_transition(1, 'Y', 2);
    this->_add_transition(1, 'Z', 2);
    this->_add_transition(1, '_', 2);

    this->_add_transition(2, 'a', 2);
    this->_add_transition(2, 'b', 2);
    this->_add_transition(2, 'c', 2);
    this->_add_transition(2, 'd', 2);
    this->_add_transition(2, 'e', 2);
    this->_add_transition(2, 'f', 2);
    this->_add_transition(2, 'g', 2);
    this->_add_transition(2, 'h', 2);
    this->_add_transition(2, 'i', 2);
    this->_add_transition(2, 'j', 2);
    this->_add_transition(2, 'k', 2);
    this->_add_transition(2, 'l', 2);
    this->_add_transition(2, 'm', 2);
    this->_add_transition(2, 'n', 2);
    this->_add_transition(2, 'o', 2);
    this->_add_transition(2, 'p', 2);
    this->_add_transition(2, 'q', 2);
    this->_add_transition(2, 'r', 2);
    this->_add_transition(2, 's', 2);
    this->_add_transition(2, 't', 2);
    this->_add_transition(2, 'u', 2);
    this->_add_transition(2, 'v', 2);
    this->_add_transition(2, 'w', 2);
    this->_add_transition(2, 'x', 2);
    this->_add_transition(2, 'y', 2);
    this->_add_transition(2, 'z', 2);
    this->_add_transition(2, 'A', 2);
    this->_add_transition(2, 'B', 2);
    this->_add_transition(2, 'C', 2);
    this->_add_transition(2, 'D', 2);
    this->_add_transition(2, 'E', 2);
    this->_add_transition(2, 'F', 2);
    this->_add_transition(2, 'G', 2);
    this->_add_transition(2, 'H', 2);
    this->_add_transition(2, 'I', 2);
    this->_add_transition(2, 'J', 2);
    this->_add_transition(2, 'K', 2);
    this->_add_transition(2, 'L', 2);
    this->_add_transition(2, 'M', 2);
    this->_add_transition(2, 'N', 2);
    this->_add_transition(2, 'O', 2);
    this->_add_transition(2, 'P', 2);
    this->_add_transition(2, 'Q', 2);
    this->_add_transition(2, 'R', 2);
    this->_add_transition(2, 'S', 2);
    this->_add_transition(2, 'T', 2);
    this->_add_transition(2, 'U', 2);
    this->_add_transition(2, 'V', 2);
    this->_add_transition(2, 'W', 2);
    this->_add_transition(2, 'X', 2);
    this->_add_transition(2, 'Y', 2);
    this->_add_transition(2, 'Z', 2);
    this->_add_transition(2, '0', 2);
    this->_add_transition(2, '1', 2);
    this->_add_transition(2, '2', 2);
    this->_add_transition(2, '3', 2);
    this->_add_transition(2, '4', 2);
    this->_add_transition(2, '5', 2);
    this->_add_transition(2, '6', 2);
    this->_add_transition(2, '7', 2);
    this->_add_transition(2, '8', 2);
    this->_add_transition(2, '9', 2);
    this->_add_transition(2, '_', 2);

    this->start_state = 1;

    this->reset();
}

Token IdentifierParser::parse(std::shared_ptr<InputStream> stream) {
    char current_symbol;
    std::string face_value = "";
    stream->forward();
    Token ret;
    if(stream->_filestream.eof()) {
        ret.type = TokenType::EOT;
        this->reset();
        return ret;
    }
    
    do {
        current_symbol = stream->get();
        if(this->alphabet.find(current_symbol) == this->alphabet.end()) {
            if(this->accept_states.find(this->current_state) != this->accept_states.end()) {

                ret.type = TokenType::IDENTIFIER;
                if(this->_keyword.match(face_value)) {
                    ret.type = TokenType::KEYWORD;
                }
                switch (this->current_state) {
                    case 2:
                        ret.object = std::make_any<std::string>(face_value);
                        break;
                    default:
                        ret.type = TokenType::INVALID;
                        break;
                }
                this->reset();
                return ret;
            } else {
                ret.type = TokenType::INVALID;
                this->reset();
                return ret;
            }
        } else {
            if (this->transitions.find({this->current_state, current_symbol}) != transitions.end()) {
                face_value += current_symbol;
                this->current_state = transitions[{this->current_state, current_symbol}];
                stream->next();
            } else {
                ret.type = TokenType::INVALID;
                this->reset();
                return ret;
            }
        }
    }while(!stream->_filestream.eof());

    ret.type = TokenType::EOT;
    this->reset();
    return ret;
}