#include "stream/token_stream.h"

TokenStream::TokenStream(std::shared_ptr<InputStream> stream) {
    this->_stream = stream;
    this->next();
    this->_current_token = this->get();
}

Token TokenStream::get() {
    if(!this->_backward.empty()) {
        Token ret = this->_backward.top();
        this->_backward.pop();
        return ret;
    }
    return this->_current_token;
}

void TokenStream::backward(Token token) {
    this->_backward.push(token);
}



void TokenStream::next() {

    Token ret;
    ret = this->_id_parser.parse(this->_stream);
    if(ret.type != TokenType::INVALID) {
        this->_current_token = ret;
        return;
    }

    ret = this->_num_parser.parse(this->_stream);
    if(ret.type != TokenType::INVALID) {
        this->_current_token = ret;
        return;
    }

    ret = this->_cs_parser.parse(this->_stream);
    if(ret.type != TokenType::INVALID) {
        this->_current_token = ret;
        return;
    }

    ret = this->_sym_parser.parse(this->_stream);
    if(ret.type != TokenType::INVALID) {
        this->_current_token = ret;
        return;
    }

    ret.type = TokenType::INVALID;
    this->_current_token = ret;
}

