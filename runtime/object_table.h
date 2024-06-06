#ifndef __PL0_OBJECT_TABLE__
#define __PL0_OBJECT_TABLE__

#include "typetable.h"

#include <unordered_map>
#include <any>
#include <optional>
#include <memory>

struct PLObject {
    PLType type;
    std::string object_name;
    bool is_constant;
    std::any value;
    std::optional<std::unordered_map<std::string, std::any>> member_value;
};

class PLObjectTable {
private:
    
};
#endif