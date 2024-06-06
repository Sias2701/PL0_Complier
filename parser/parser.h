#ifndef __PL0_PARSER__
#define __PL0_PARSER__

#include "stream/token_stream.h"
#include "token/token.h"
#include "token/charstr.h"
#include "token/identifier.h"
#include "token/keyword.h"
#include "token/symbol.h"
#include "semantic/semantic.h"
#include "parser/statement.h"
#include <memory>

class PLParser {
protected:
    std::shared_ptr<TokenStream> stream;
public:
    PLParser(std::shared_ptr<TokenStream> stream) {
        this->stream = stream;
    };
    PLParser() = default;
    virtual PLStatement parse() {
        PLStatement stmt;
        stmt.action = PLStatementAction::VOID;
        return stmt;
    };
};

class PLIntermediateParser {
protected:
    std::shared_ptr<TokenStream> stream;
public:
    PLIntermediateParser(std::shared_ptr<TokenStream> stream) {
        this->stream = stream;
    };
    PLIntermediateParser() = default;
    virtual SemanticToken parse() {
        SemanticToken ret;
        ret.type = SemanticTokenType::VOID;
        return ret;
    };
};

#endif