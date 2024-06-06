#ifndef __PL0_CONDITION_FACTOR__
#define __PL0_CONDITION_FACTOR__

#include "parser/parser.h"
#include "parser/condition.h"
#include "parser/expression.h"

class PLConditionFactorParser : virtual public PLIntermediateParser{
    std::shared_ptr<std::vector<SemanticToken>> suffix_stack;
    std::shared_ptr<std::stack<SemanticToken>> operator_stack;
public:
    PLConditionFactorParser(std::shared_ptr<TokenStream> stream);
    SemanticToken parse();
};



#endif