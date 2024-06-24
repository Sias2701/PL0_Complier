#ifndef __PL0_VM__
#define __PL0_VM__

#include "vm/instruction.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#define PRESERVED_STACK_SIZE 1024

class VirtualMachine {
private:
    std::vector<WORD> mem;
    WORD reg[10];
public:
    VirtualMachine() = default;
    void load(std::string input_file) {
        size_t vecSize;
        std::ifstream inFile(input_file, std::ios::binary);
        inFile.read(reinterpret_cast<char*>(&vecSize), sizeof(vecSize));
        this->mem.resize(vecSize + 100);
        inFile.read(reinterpret_cast<char*>(this->mem.data()), vecSize * sizeof(WORD));
        inFile.close();
        this->reg[IP] = 0;
        this->reg[SP] = this->reg[BP] = static_cast<WORD>(vecSize) + 1;
    }
    void run();
};

#endif