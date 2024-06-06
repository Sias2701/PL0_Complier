#include "charstr.h"

CharStrParser::CharStrParser() {
    std::string printable = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ ";
    std::string accept_char = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&()*+,-./:;<=>?@[\\]^_`{|}~ ";
    std::string accept_string = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ ";
    for(char i : printable) {
        this->alphabet.insert(i);
    }

    this->states = {1, 2, 3, 4, 5, 6};
    this->accept_states = {4, 6};

    this->first = {'\'', '"'};
    
    this->_add_transition(1, '\'', 2);

    for(char i : accept_char) {
        this->_add_transition(2, i, 3);
    }

    this->_add_transition(3, '\'', 4);

    this->_add_transition(1, '"', 5);

    for(char i : accept_string) {
        this->_add_transition(5, i, 5);
    }

     this->_add_transition(5, '"', 6);
    this->start_state = 1;
    this->reset();
}

Token CharStrParser::parse(std::shared_ptr<InputStream> stream) {
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
        if(this->accept_states.find(this->current_state) != this->accept_states.end()) {
                switch (this->current_state) {
                    case 4:
                        ret.type = TokenType::CHAR;
                        break;
                    case 6:
                        ret.type = TokenType::STRING;
                        break;
                    default:
                        ret.type = TokenType::INVALID;
                        break;
                }
                ret.object = std::make_any<std::string>(face_value);
                this->reset();
                return ret;
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