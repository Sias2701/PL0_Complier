#ifndef __PL0_NUMBER_TOKEN__
#define __PL0_NUMBER_TOKEN__

#include "dfa.h"
#include <variant>

typedef std::variant<int, float> PL0Number;


class NumberParser final : virtual public DFA {
public:
    NumberParser();
    Token parse(std::shared_ptr<InputStream> stream);
};

#endif