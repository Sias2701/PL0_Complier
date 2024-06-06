#ifndef __PL0_IDENTIFIER_TOKEN__
#define __PL0_IDENTIFIER_TOKEN__

#include "dfa.h"
#include "token/keyword.h"
class IdentifierParser final : virtual public DFA {
    KeywordMatcher _keyword;
public:
    IdentifierParser();
    Token parse(std::shared_ptr<InputStream> stream);
};

#endif