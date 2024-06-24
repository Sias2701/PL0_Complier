#include "vm/instruction.h"

WORD prepare_inst(WORD opcode, WORD op1, WORD op2) {
    return ((opcode & 0xffff) << 16) | ((op1 & 0xff) << 8) | (op2 & 0xff);
}

WORD int_to_word(int i) {
    return *reinterpret_cast<WORD*>(&i);
}

WORD char_to_word(char c) {
    return static_cast<unsigned int>(c) & 0xff;
}

WORD float_to_word(float f) {
    return *reinterpret_cast<WORD*>(&f);
}