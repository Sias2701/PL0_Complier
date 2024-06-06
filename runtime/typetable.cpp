#include "runtime/typetable.h"

PLTypeTable::PLTypeTable() {
    PLType int_;
    int_.category = PLTypeCategory::BASIC;
    int_.name = "integer";

    PLType float_;
    float_.category = PLTypeCategory::BASIC;
    float_.name = "float";

    PLType char_;
    char_.category = PLTypeCategory::BASIC;
    char_.name = "char";
    this->insert(int_);
    this->insert(float_);
    this->insert(char_);
};

void PLTypeTable::insert(PLType type) {
    this->_type_table.insert(type);
}

PLType PLTypeTable::query(std::string type_name) {
    PLType tmp;
    tmp.name = type_name;
    auto it = this->_type_table.find(tmp);

    if (it != this->_type_table.end()) {
        return *it;
    } else {
        throw RuntimeError("Type not exist");
    }
}