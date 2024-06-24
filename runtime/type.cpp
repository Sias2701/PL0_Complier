#include "runtime/type.h"

size_t PLType::size() {
    switch (this->category)
    {
        case PLTypeCategory::BASIC:
            return 4;

        case PLTypeCategory::STRUCT:
        {
            if(this->member.has_value() ==false) {
                return 0;
            }
            size_t ret = 0;
            std::vector<std::pair<PLType, std::string>> list = this->member.value();
            for (auto& p : list) {
                ret += p.first.size();
            }
        }
        
        case PLTypeCategory::ARRAY: {
            if(this->array_context.has_value() ==false) {
                return 0;
            }
            std::pair<PLType, size_t> ctx = array_context.value();
            return ctx.first.size() * ctx.second;
        }

        default:
            return 0;
            break;
    }
}