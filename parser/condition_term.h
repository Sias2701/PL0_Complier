#ifndef __PL0_CONDITION_TERM__
#define __PL0_CONDITION_TERM__

#include "parser/parser.h"
#include "parser/condition_factor.h"
#include "parser/condition.h"

class PLConditionTermParser : virtual public PLIntermediateParser{
    
public:
    PLConditionTermParser(std::shared_ptr<TokenStream> stream);
    SemanticToken parse();
};



#endif