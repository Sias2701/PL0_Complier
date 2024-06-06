#include "stream/input_stream.h"

InputStream::InputStream(std::string input_file) {
    this->_filestream = std::ifstream(input_file);
}

void InputStream::next() {
    if(!this->_backward.empty()) {
        this->_backward.pop();

        return;
    }
    this->_filestream.ignore();
    int i = 1;
    
}


std::streampos InputStream::position() {
    return this->_filestream.tellg();
}

void InputStream::forward() {
    while (std::isspace(this->get()))
    {
        this->next();
    }
}

char InputStream::get() {
    if(!this->_backward.empty()) {
        char ret = this->_backward.top();
        return ret;
    }
    if(this->_filestream.eof()) {
        if(this->_multiline_bracket_match.size() != 0) {
            throw MLBracketNotMatchException();
        }
        return 0;
    }

    char comment1 = this->_filestream.peek();

    if (comment1 == '/') {
        std::streampos current = this->_filestream.tellg();
        this->_filestream.ignore();
        char comment2 = _filestream.peek();
        switch (comment2)
        {
            case '/':
                do {
                    this->_filestream.ignore();
                }while(this->_filestream.peek() != '\n' && !this->_filestream.eof());
                break;
            case '*':
                char next1;
                char next2;
                this->_multiline_bracket_match.push(MLBracket::LEFT);
                do {
                    next1 = this->_filestream.get();
                    next2 = this->_filestream.peek();
                }while (!(next1 == '*' && next2 == '/') && !this->_filestream.eof());
                if(next1 == '*' && next2 == '/' && this->_multiline_bracket_match.top() == MLBracket::LEFT) {
                    this->_multiline_bracket_match.pop();
                }
                this->next();
                this->_backward.push(' ');
                return this->_backward.top();
                break;
            default:
                this->_filestream.seekg(current);
                return this->_filestream.peek();
        }
    }

    if(this->_filestream.eof()) {
        if(this->_multiline_bracket_match.size() != 0) {
            throw MLBracketNotMatchException();
        }
        return 0;
    }

    return this->_filestream.peek();
}

void InputStream::reset() {
    this->_filestream.seekg(std::streampos(0));
}

void InputStream::set(std::streampos pos) {
    this->_filestream.seekg(pos);
}

void InputStream::backward(char symbol) {
    this->_backward.push(symbol);
}