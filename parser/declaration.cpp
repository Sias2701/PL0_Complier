#include "parser/declaration.h"

PLDelcarationParser::PLDelcarationParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
}

PLStatement PLDelcarationParser::parse() {
    Token current_token = this->stream->get();
    PLStatement ret;
    if(current_token.type != TokenType::KEYWORD) {
        ret.action = PLStatementAction::INVALID;
        return ret;
    }
}
