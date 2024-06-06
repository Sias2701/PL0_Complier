#ifndef __PL0_CHARSTR_TOKEN__
#define __PL0_CHARSTR_TOKEN__

#include "token/dfa.h"

class CharStrParser final : virtual public DFA {
public:
    CharStrParser();
    Token parse(std::shared_ptr<InputStream> stream);
};

#endif