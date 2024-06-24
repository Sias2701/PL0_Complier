#ifndef __PL0_FUNCTION_TABLE__
#define __PL0_FUNCTION_TABLE__

#include "typetable.h"
#include "statement.h"
#include <unordered_map>
#include <utility>
#include <optional>
#include <memory>

struct PLFunction {
    PLType ret_type;
    std::string name;
    std::vector<std::pair<PLType, std::string>> arguments;
    std::vector<PLStatement> func_body;
};

class PLFunctionTable {
private:
    
};

#endif