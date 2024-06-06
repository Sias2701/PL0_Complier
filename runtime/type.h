#ifndef __PL0_TYPE__
#define __PL0_TYPE__

#include <string>
#include <optional>
#include <vector>
#include <utility>

enum class PLTypeCategory : unsigned char{
    BASIC,
    STRUCT,
    ARRAY,
    ALIAS
};


#endif 