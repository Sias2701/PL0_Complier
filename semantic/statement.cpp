#include "statement.h"

PLStatementParser::PLStatementParser(std::shared_ptr<TokenStream> stream) {
    this->stream = stream;
}