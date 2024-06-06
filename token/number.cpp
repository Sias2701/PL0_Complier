#include "number.h"

NumberParser::NumberParser() {
    this->alphabet = {
        '0', '1', '2', '3', '4', 
        '5', '6', '7', '8', '9', 
        'A', 'B', 'C', 'D', 'E', 'F',
        'a', 'b', 'c', 'd', 'e', 'f',
        'o', 'x', 'O', 'X', '.'
    };

    this->first = {
        '0', '1', '2', '3', '4', 
        '5', '6', '7', '8', '9'
    };

    this->states = {
        1, 4, 7, 2, 8, 3, 6, 9, 5
    };

    this->accept_states = {
        4, 2, 3, 6, 5
    };

    this->_add_transition(1, '0', 4);

    this->_add_transition(1, '1', 6);
    this->_add_transition(1, '2', 6);
    this->_add_transition(1, '3', 6);
    this->_add_transition(1, '4', 6);
    this->_add_transition(1, '5', 6);
    this->_add_transition(1, '6', 6);
    this->_add_transition(1, '7', 6);
    this->_add_transition(1, '8', 6);
    this->_add_transition(1, '9', 6);

    this->_add_transition(6, '0', 6);
    this->_add_transition(6, '1', 6);
    this->_add_transition(6, '2', 6);
    this->_add_transition(6, '3', 6);
    this->_add_transition(6, '4', 6);
    this->_add_transition(6, '5', 6);
    this->_add_transition(6, '6', 6);
    this->_add_transition(6, '7', 6);
    this->_add_transition(6, '8', 6);
    this->_add_transition(6, '9', 6);

    this->_add_transition(6, '.', 9);

    this->_add_transition(9, '0', 5);
    this->_add_transition(9, '1', 5);
    this->_add_transition(9, '2', 5);
    this->_add_transition(9, '3', 5);
    this->_add_transition(9, '4', 5);
    this->_add_transition(9, '5', 5);
    this->_add_transition(9, '6', 5);
    this->_add_transition(9, '7', 5);
    this->_add_transition(9, '8', 5);
    this->_add_transition(9, '9', 5);

    this->_add_transition(5, '0', 5);
    this->_add_transition(5, '1', 5);
    this->_add_transition(5, '2', 5);
    this->_add_transition(5, '3', 5);
    this->_add_transition(5, '4', 5);
    this->_add_transition(5, '5', 5);
    this->_add_transition(5, '6', 5);
    this->_add_transition(5, '7', 5);
    this->_add_transition(5, '8', 5);
    this->_add_transition(5, '9', 5);

    this->_add_transition(4, 'o', 7);
    this->_add_transition(4, 'O', 7);

    this->_add_transition(7, '0', 2);
    this->_add_transition(7, '1', 2);
    this->_add_transition(7, '2', 2);
    this->_add_transition(7, '3', 2);
    this->_add_transition(7, '4', 2);
    this->_add_transition(7, '5', 2);
    this->_add_transition(7, '6', 2);
    this->_add_transition(7, '7', 2);

    this->_add_transition(2, '0', 2);
    this->_add_transition(2, '1', 2);
    this->_add_transition(2, '2', 2);
    this->_add_transition(2, '3', 2);
    this->_add_transition(2, '4', 2);
    this->_add_transition(2, '5', 2);
    this->_add_transition(2, '6', 2);
    this->_add_transition(2, '7', 2);

    this->_add_transition(4, 'x', 8);
    this->_add_transition(4, 'X', 8);

    this->_add_transition(8, '0', 3);
    this->_add_transition(8, '1', 3);
    this->_add_transition(8, '2', 3);
    this->_add_transition(8, '3', 3);
    this->_add_transition(8, '4', 3);
    this->_add_transition(8, '5', 3);
    this->_add_transition(8, '6', 3);
    this->_add_transition(8, '7', 3);
    this->_add_transition(8, '8', 3);
    this->_add_transition(8, '9', 3);
    this->_add_transition(8, 'A', 3);
    this->_add_transition(8, 'B', 3);
    this->_add_transition(8, 'C', 3);
    this->_add_transition(8, 'D', 3);
    this->_add_transition(8, 'E', 3);
    this->_add_transition(8, 'F', 3);
    this->_add_transition(8, 'a', 3);
    this->_add_transition(8, 'b', 3);
    this->_add_transition(8, 'c', 3);
    this->_add_transition(8, 'd', 3);
    this->_add_transition(8, 'e', 3);
    this->_add_transition(8, 'f', 3);

    this->_add_transition(3, '0', 3);
    this->_add_transition(3, '1', 3);
    this->_add_transition(3, '2', 3);
    this->_add_transition(3, '3', 3);
    this->_add_transition(3, '4', 3);
    this->_add_transition(3, '5', 3);
    this->_add_transition(3, '6', 3);
    this->_add_transition(3, '7', 3);
    this->_add_transition(3, '8', 3);
    this->_add_transition(3, '9', 3);
    this->_add_transition(3, 'A', 3);
    this->_add_transition(3, 'B', 3);
    this->_add_transition(3, 'C', 3);
    this->_add_transition(3, 'D', 3);
    this->_add_transition(3, 'E', 3);
    this->_add_transition(3, 'F', 3);
    this->_add_transition(3, 'a', 3);
    this->_add_transition(3, 'b', 3);
    this->_add_transition(3, 'c', 3);
    this->_add_transition(3, 'd', 3);
    this->_add_transition(3, 'e', 3);
    this->_add_transition(3, 'f', 3);
    this->start_state = 1;

    this->current_state = this->start_state;
}

Token NumberParser::parse(std::shared_ptr<InputStream> stream) {
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

                ret.type = TokenType::NUMBER;
                switch (this->current_state) {
                    case 4:
                        ret.object = std::make_any<PL0Number>(0);
                        break;
                    case 2:
                        ret.object = std::make_any<PL0Number>(std::stoi(face_value.substr(2), nullptr, 8));
                        break;
                    case 3:
                        ret.object = std::make_any<PL0Number>(std::stoi(face_value, nullptr, 16));
                        break;
                    case 6:
                        ret.object = std::make_any<PL0Number>(std::stoi(face_value, nullptr, 10));
                        break;
                    case 5:
                        ret.object = std::make_any<PL0Number>(std::stof(face_value, nullptr));
                        break;
                    default:
                        ret.type = TokenType::INVALID;
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