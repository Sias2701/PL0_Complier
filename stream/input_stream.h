#ifndef __PL0_INPUT_STREAM__
#define __PL0_INPUT_STREAM__

#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <stack>

class MLBracketNotMatchException : public std::exception {
public:
    MLBracketNotMatchException() : message_("Multiline comment bracket not matched!") {}

    virtual const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class InputStream {
private:
    enum class MLBracket : char{
        LEFT,
        RIGHT
    };
    std::stack<MLBracket> _multiline_bracket_match;
    std::stack<char> _backward;

public:
    std::ifstream _filestream;
    InputStream(std::string input_file);
    InputStream() = default;
    ~InputStream() = default;
    std::streampos position();

    char get();
    void next();
    void reset();
    void set(std::streampos pos);
    void forward(); 
    void backward(char symbol);
};

#endif