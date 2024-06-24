#ifndef __PL0_TYPE_TABLE__
#define __PL0_TYPE_TABLE__

#include <string>
#include <optional>
#include <vector>
#include <unordered_set>
#include <exception>

#include "runtime/type.h"
#include "runtime/runtime.h"

class RedefinitionException : std::exception {

};

class MemberNotExistException : std::exception {

};

struct PLTypeHash {
    size_t operator()(const PLType& info) const {
        return std::hash<std::string>()(info.name);
    }
};

struct PLTypeEqual {
    bool operator()(const PLType& lhs, const PLType& rhs) const {
        return lhs.name == rhs.name;
    }
};

class PLTypeTable {
private:
    std::unordered_set<PLType, PLTypeHash, PLTypeEqual> _type_table;

public:
    PLTypeTable();
    void insert(PLType type);
    PLType query(std::string type_name);
};

#endif