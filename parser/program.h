#ifndef __PL0_PROGRAM__
#define __PL0_PROGRAM__

#include "parser/parser.h"

class PLProgramParser final : virtual public PLParser {
public:
    PLProgramParser(std::shared_ptr<TokenStream> stream);
    PLStatement parse();
};

#endif