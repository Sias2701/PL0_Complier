#ifndef __PL0_DECLARATION__
#define __PL0_DECLARATION__

#include "parser/parser.h"
#include "runtime/type_table.h"

class PLDelcarationParser : virtual public PLParser{
public:
    PLDelcarationParser(std::shared_ptr<TokenStream> stream);
    PLStatement parse();
};

struct PLDelcarationInfo {
    PLType type;
    std::vector<std::string> id;
    std::optional<std::vector<std::any>> value;
};

#endif