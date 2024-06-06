#include "parser/program.h"

PLProgramParser::PLProgramParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
}

PLStatement PLProgramParser::parse() {
    Token current_token = this->stream->get();
    PLStatement ret;
    if(current_token.type == TokenType::EOT) {
        ret.action = PLStatementAction::EOS;
        return ret;
    }

    if(current_token.type == TokenType::KEYWORD) {
        
    } else {

    }

    return ret;
}