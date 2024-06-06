#include "vm/vm.h"

void VirtualMachine::run() {
    bool run_var = true;
    while (run_var)
    {

        WORD current_word = this->mem[this->reg[IP]];
        WORD inst = (current_word >> 16) & 0xFFFFu;
        WORD op1_type = (current_word >> 8) & 0xFFu;
        WORD op2_type = (current_word) & 0xFFu;

        switch (inst)
        {
            case HALT: {
                std::cout << "[VM] HALT" << std::endl;
                run_var = false;
                break;
            }

            case PUSH: {
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        if(++this->reg[SP] >= this->mem.size()) throw "OUT OF MEM";
                        this->mem[this->reg[SP]] = current_word;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(++this->reg[SP] >= this->mem.size()) throw "OUT OF MEM";
                        if(current_word >= MAXREG) throw "INVALID REG";
                        this->mem[this->reg[SP]] = this->reg[current_word];
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(++this->reg[SP] >= this->mem.size() || current_word >= this->mem.size()) throw "OUT OF MEM";
                        this->mem[this->reg[SP]] = this->mem[current_word];
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case POP: {
                switch (op1_type)
                {
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        this->reg[current_word] = this->mem[this->reg[SP]--];
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        this->mem[current_word] = this->mem[this->reg[SP]--];
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case READW: {
                int input;
                std::cin >> input;
                WORD mem_ctx = *reinterpret_cast<unsigned int*>(&input);
                switch (op1_type)
                {
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        this->reg[current_word] = mem_ctx;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                        this->mem[current_word] = mem_ctx;
                        break;
                    case SEG: {
                        switch (op2_type)
                        {
                            case IMM:
                                current_word = this->mem[++this->reg[IP]];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                this->mem[current_word] = mem_ctx;
                                break;
                            case REG:
                                current_word = this->mem[++this->reg[IP]];
                                if(current_word >= MAXREG) throw "INVALID REG";
                                current_word = this->reg[current_word];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                this->mem[current_word] = mem_ctx;
                                break;

                            default:
                                throw "INVALID MEM ADDR";
                        }
                        break;
                    }
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case READB: {
                char input;
                std::cin >> input;
                WORD mem_ctx = static_cast<unsigned int>(input);
                switch (op1_type)
                {
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        this->reg[current_word] = mem_ctx;
                        break;
                    case MEM:
                         current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                        this->mem[current_word] = mem_ctx;
                        break;
                    case SEG: {
                        switch (op2_type)
                        {
                            case IMM:
                                current_word = this->mem[++this->reg[IP]];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                this->mem[current_word] = mem_ctx;
                                break;
                            case REG:
                                current_word = this->mem[++this->reg[IP]];
                                if(current_word >= MAXREG) throw "INVALID REG";
                                current_word = this->reg[current_word];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                this->mem[current_word] = mem_ctx;
                                break;

                            default:
                                throw "INVALID MEM ADDR";
                        }
                        break;
                    }
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case READF: {
                float input;
                std::cin >> input;
                WORD mem_ctx = *reinterpret_cast<unsigned int*>(&input);
                switch (op1_type)
                {
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        this->reg[current_word] = mem_ctx;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                        this->mem[current_word] = mem_ctx;
                        break;
                    case SEG: {
                        switch (op2_type)
                        {
                            case IMM:
                                current_word = this->mem[++this->reg[IP]];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                this->mem[current_word] = mem_ctx;
                                break;
                            case REG:
                                current_word = this->mem[++this->reg[IP]];
                                if(current_word >= MAXREG) throw "INVALID REG";
                                current_word = this->reg[current_word];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                this->mem[current_word] = mem_ctx;
                                break;

                            default:
                                throw "INVALID MEM ADDR";
                        }
                        break;
                    }
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case WRITEW: {
                int input = 0;
                WORD mem_ctx;
                switch (op1_type)
                {
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        mem_ctx = this->reg[current_word];
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                        mem_ctx = this->mem[current_word];
                        break;
                    case SEG: {
                        switch (op2_type)
                        {
                            case IMM:
                                current_word = this->mem[++this->reg[IP]];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                mem_ctx = this->mem[current_word];
                                break;
                            case REG:
                                current_word = this->mem[++this->reg[IP]];
                                if(current_word >= MAXREG) throw "INVALID REG";
                                current_word = this->reg[current_word];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                mem_ctx = this->mem[current_word];
                                break;

                            default:
                                throw "INVALID MEM ADDR";
                        }
                        break;
                    }
                    default:
                        throw "INVALID INSTRUCTION";
                }
                input = *reinterpret_cast<int*>(&mem_ctx);
                std::cout << input << std::endl;
                break;
            }

            case WRITEB: {
                char input;
                WORD mem_ctx;
                switch (op1_type)
                {
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        mem_ctx = this->reg[current_word];
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                        mem_ctx = this->mem[current_word];
                        break;
                    case SEG: {
                        switch (op2_type)
                        {
                            case IMM:
                                current_word = this->mem[++this->reg[IP]];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                this->mem[current_word] = mem_ctx;
                                break;
                            case REG:
                                current_word = this->mem[++this->reg[IP]];
                                if(current_word >= MAXREG) throw "INVALID REG";
                                current_word = this->reg[current_word];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                this->mem[current_word] = mem_ctx;
                                break;

                            default:
                                throw "INVALID MEM ADDR";
                        }
                        break;
                    }
                    default:
                        throw "INVALID INSTRUCTION";
                }
                input = static_cast<char>(mem_ctx);
                std::cout << input << std::endl;
                break;
            }

            case WRITEF: {
                float input;
                WORD mem_ctx;
                switch (op1_type)
                {
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        mem_ctx = this->reg[current_word];
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                        mem_ctx = this->mem[current_word];
                        break;
                    case SEG: {
                        switch (op2_type)
                        {
                            case IMM:
                                current_word = this->mem[++this->reg[IP]];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                mem_ctx = this->mem[current_word];
                                break;
                            case REG:
                                current_word = this->mem[++this->reg[IP]];
                                if(current_word >= MAXREG) throw "INVALID REG";
                                current_word = this->reg[current_word];
                                current_word += this->reg[BP];
                                if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                                mem_ctx = this->mem[current_word];
                                break;

                            default:
                                throw "INVALID MEM ADDR";
                        }
                        break;
                    }
                    default:
                        throw "INVALID INSTRUCTION";
                }
                input = *reinterpret_cast<float*>(&mem_ctx);
                std::cout << input << std::endl;
                break;
            }

            case CMPW: {
                int op1;
                int op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case EMP:
                        op2 = op1;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                /* SR 32 EQ FLAG*/
                if(op1 == op2) {
                    this->reg[SR] |= 0b10000000000000000000000000000000;
                } else {
                    this->reg[SR] &= 0b01111111111111111111111111111111;
                }

                /* SR 31 GT FLAG SR 30 LS FLAG*/
                if(op1 > op2) {
                    this->reg[SR] |= 0b01000000000000000000000000000000;
                    this->reg[SR] &= 0b10111111111111111111111111111111;
                } else if (op1 < op2) {
                    this->reg[SR] |= 0b00100000000000000000000000000000;
                    this->reg[SR] &= 0b11011111111111111111111111111111;
                }

                /* SR 29 ODD FLAG*/
                if(op1 % 2 == 0) {
                    this->reg[SR] |= 0b00010000000000000000000000000000;
                } else {
                    this->reg[SR] &= 0b11101111111111111111111111111111;
                }
                break;
            }

            case CMPF: {
                float op1;
                float op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                /* SR 32 EQ FLAG*/
                if(op1 == op2) {
                    this->reg[SR] |= 0b10000000000000000000000000000000;
                } else {
                    this->reg[SR] &= 0b01111111111111111111111111111111;
                }

                /* SR 31 GT FLAG SR 30 LS FLAG*/
                if(op1 > op2) {
                    this->reg[SR] |= 0b01000000000000000000000000000000;
                    this->reg[SR] &= 0b11011111111111111111111111111111;
                } else if (op1 < op2) {
                    this->reg[SR] |= 0b00100000000000000000000000000000;
                    this->reg[SR] &= 0b10111111111111111111111111111111;
                }
                break;
            }

            case CMPB: {
                unsigned int op1;
                unsigned int op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                /* SR 32 EQ FLAG*/
                if(op1 == op2) {
                    this->reg[SR] |= 0b10000000000000000000000000000000;
                } else {
                    this->reg[SR] &= 0b01111111111111111111111111111111;
                }

                /* SR 31 GT FLAG SR 30 LS FLAG*/
                if(op1 > op2) {
                    this->reg[SR] |= 0b01000000000000000000000000000000;
                    this->reg[SR] &= 0b10111111111111111111111111111111;
                } else if (op1 < op2) {
                    this->reg[SR] |= 0b00100000000000000000000000000000;
                    this->reg[SR] &= 0b11011111111111111111111111111111;
                }
                break;
            }

            case JMP: {
                current_word = this->mem[++this->reg[IP]];
                switch (op1_type)
                {
                    case IMM:
                        if(this->reg[IP] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = current_word - 1;
                        break;
                    case REG:
                        if(current_word >= MAXREG) throw "INVALID REG";
                        if(this->reg[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->reg[current_word] - 1;
                        break;
                    case MEM:
                        if(current_word >= this->mem.size() || this->mem[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->mem[current_word] - 1;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case JG: {
                current_word = this->mem[++this->reg[IP]];
                if((this->reg[SR] & 0b01000000000000000000000000000000) == 0) {
                    break;
                }
                switch (op1_type)
                {
                    case IMM:
                        if(this->reg[IP] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = current_word - 1;
                        break;
                    case REG:
                        if(current_word >= MAXREG) throw "INVALID REG";
                        if(this->reg[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->reg[current_word] - 1;
                        break;
                    case MEM:
                        if(current_word >= this->mem.size() || this->mem[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->mem[current_word] - 1;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case JL: {
                current_word = this->mem[++this->reg[IP]];
                if((this->reg[SR] & 0b00100000000000000000000000000000) == 0) {
                    break;
                }
                switch (op1_type)
                {
                    case IMM:
                        if(this->reg[IP] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = current_word - 1;
                        break;
                    case REG:
                        if(current_word >= MAXREG) throw "INVALID REG";
                        if(this->reg[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->reg[current_word] - 1;
                        break;
                    case MEM:
                        if(current_word >= this->mem.size() || this->mem[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->mem[current_word]- 1;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case JE: {
                current_word = this->mem[++this->reg[IP]];
                if((this->reg[SR] & 0b10000000000000000000000000000000) == 0) {
                    break;
                }
                switch (op1_type)
                {
                    case IMM:
                        if(this->reg[IP] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = current_word - 1;
                        break;
                    case REG:
                        if(current_word >= MAXREG) throw "INVALID REG";
                        if(this->reg[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->reg[current_word]- 1;
                        break;
                    case MEM:
                        if(current_word >= this->mem.size() || this->mem[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->mem[current_word] - 1;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case JNE: {
                current_word = this->mem[++this->reg[IP]];
                if((this->reg[SR] & 0b10000000000000000000000000000000) == 1) {
                    break;
                }
                switch (op1_type)
                {
                    case IMM:
                        if(this->reg[IP] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = current_word - 1;
                        break;
                    case REG:
                        if(current_word >= MAXREG) throw "INVALID REG";
                        if(this->reg[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->reg[current_word]- 1;
                        break;
                    case MEM:
                        if(current_word >= this->mem.size() || this->mem[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->mem[current_word]- 1;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case JEG: {
                current_word = this->mem[++this->reg[IP]];
                if((this->reg[SR] & 0b11000000000000000000000000000000) == 0) {
                    break;
                }
                switch (op1_type)
                {
                    case IMM:
                        if(this->reg[IP] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = current_word - 1;
                        break;
                    case REG:
                        if(current_word >= MAXREG) throw "INVALID REG";
                        if(this->reg[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->reg[current_word]- 1;
                        break;
                    case MEM:
                        if(current_word >= this->mem.size() || this->mem[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->mem[current_word]- 1;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case JEL: {
                current_word = this->mem[++this->reg[IP]];
                if((this->reg[SR] & 0b10100000000000000000000000000000) == 0) {
                    break;
                }
                switch (op1_type)
                {
                    case IMM:
                        if(this->reg[IP] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = current_word - 1;
                        break;
                    case REG:
                        if(current_word >= MAXREG) throw "INVALID REG";
                        if(this->reg[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->reg[current_word] - 1;
                        break;
                    case MEM:
                        if(current_word >= this->mem.size() || this->mem[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->mem[current_word] - 1;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case JODD: {
                current_word = this->mem[++this->reg[IP]];
                if((this->reg[SR] & 0b00010000000000000000000000000000) == 0) {
                    break;
                }
                switch (op1_type)
                {
                    case IMM:
                        if(this->reg[IP] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = current_word - 1;
                        break;
                    case REG:
                        if(current_word >= MAXREG) throw "INVALID REG";
                        if(this->reg[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->reg[current_word] - 1;
                        break;
                    case MEM:
                        if(current_word >= this->mem.size() || this->mem[current_word] >= this->mem.size()) throw "OUT OF MEM";
                        this->reg[IP] = this->mem[current_word]- 1;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }
            
            case ADDW: {
                int op1;
                int op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                int res = op1 + op2;
                this->reg[RR] = *reinterpret_cast<WORD*>(&res);
                break;                
            }

            case SUBW: {
                int op1;
                int op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                int res = op1 - op2;
                this->reg[RR] = *reinterpret_cast<WORD*>(&res);
                break;
            }

            case MULW: {
                int op1;
                int op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                int res = op1 * op2;
                this->reg[RR] = *reinterpret_cast<WORD*>(&res);
                break;
            }
            
            case DIVW: {
                int op1;
                int op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                int res = op1 / op2;
                this->reg[RR] = *reinterpret_cast<WORD*>(&res);
                break;
            }

            case ADDB: {
                char op1;
                char op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                int res = (op1 + op2) & 0xff;
                this->reg[RR] = *reinterpret_cast<WORD*>(&res);
                break;
            }

            case SUBB: {
                char op1;
                char op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                int res = (op1 - op2) & 0xff;
                this->reg[RR] = *reinterpret_cast<WORD*>(&res);
                break;
            }

            case MULB: {
                char op1;
                char op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                int res = (op1 * op2) & 0xff;
                this->reg[RR] = *reinterpret_cast<WORD*>(&res);
                break;
            }

            case DIVB: {
                char op1;
                char op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<unsigned int*>(&current_word) & 0xff;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                int res = ((op1 & 0xff) / (op2 & 0xff)) & 0xff;
                this->reg[RR] = *reinterpret_cast<WORD*>(&res);
                break;
            }

            case ADDF: {
                float op1;
                float op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                float res = (op1 + op2);
                this->reg[FR] = *reinterpret_cast<WORD*>(&res);
                break;
            }

            case SUBF: {
                float op1;
                float op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                float res = (op1 - op2);
                this->reg[FR] = *reinterpret_cast<WORD*>(&res);
                break;
            }

            case MULF: {
                float op1;
                float op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<float*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<float*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                float res = (op1 * op2);
                this->reg[FR] = *reinterpret_cast<WORD*>(&res);
                break;
            }
            
            case DIVF: {
                float op1;
                float op2;
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op1 = *reinterpret_cast<int*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        op2 = *reinterpret_cast<int*>(&current_word);
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                float res = (op1 / op2);
                this->reg[FR] = *reinterpret_cast<WORD*>(&res);
                break;  
            }

            case CVTW: {
                switch (op1_type)
                {
                    case MEM: {
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                        float val1 = *reinterpret_cast<float*>(&this->mem[current_word]);
                        int val2 = static_cast<int>(std::floor(val1));
                        this->mem[current_word] = *reinterpret_cast<WORD*>(&val2);
                        break;
                    }
                    case SEG: {
                        float val1 = *reinterpret_cast<float*>(&this->mem[this->reg[SP]]);
                        int val2 = static_cast<int>(std::floor(val1));
                        this->mem[this->reg[SP]] = *reinterpret_cast<WORD*>(&val2);
                        break;
                    }
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case CVTF: {
                switch (op1_type)
                {
                    case MEM:
                    {
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                        int val1 = *reinterpret_cast<int*>(&this->mem[current_word]);
                        float val2 = static_cast<float>(val1);
                        this->mem[current_word] = *reinterpret_cast<WORD*>(&val2);
                        break;
                    }
                    case SEG: {
                        int val1 = *reinterpret_cast<int*>(&this->mem[this->reg[SP]]);
                        float val2 = static_cast<int>(std::floor(val1));
                        this->mem[this->reg[SP]] = *reinterpret_cast<WORD*>(&val2);
                        break;
                    }
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            case CALL: {
                switch (op1_type)
                {
                    case IMM:
                        current_word = this->mem[++this->reg[IP]];
                        ++this->reg[SP];
                        if(this->reg[SP] >= this->mem.size()) throw "OUT OF MEM";
                        this->mem[this->reg[SP]] = this->reg[IP] + 1;

                        this->reg[IP] = current_word - 1;
                        break;
                    case REG:
                        current_word = this->mem[++this->reg[IP]];

                        ++this->reg[SP];
                        if(this->reg[SP] >= this->mem.size()) throw "OUT OF MEM";
                        this->mem[this->reg[SP]] = this->reg[IP] + 1;

                        if(current_word >= MAXREG) throw "INVALID REG";
                        current_word = this->reg[current_word];
                        this->reg[IP] = current_word - 1;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];

                        ++this->reg[SP];
                        if(this->reg[SP] >= this->mem.size()) throw "OUT OF MEM";
                        this->mem[this->reg[SP]] = this->reg[IP] + 1;

                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        current_word = this->mem[current_word];
                        this->reg[IP] = current_word - 1;
                        break;
                    default:
                        throw "INVALID INSTRUCTION";
                }

                break;
            }

            case RET: {
                this->reg[IP] = this->mem[this->reg[SP]--];
                this->reg[IP]--;
                break;
            }

            case MOV: {
                WORD op1;
                switch (op1_type)
                {
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        op1 = this->reg[current_word];
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        op1 = this->mem[current_word];
                        break;
                    case SEG: {
                        current_word = this->mem[++this->reg[IP]];
                        current_word += this->reg[BP];
                        if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                        op1 = this->mem[current_word];
                        break;
                    }

                    default:
                        throw "INVALID INSTRUCTION";
                }

                switch (op2_type)
                {
                    case REG:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= MAXREG) throw "INVALID REG";
                        this->reg[current_word] = op1;
                        break;
                    case MEM:
                        current_word = this->mem[++this->reg[IP]];
                        if(current_word >= this->mem.size()) throw "OUT OF MEM";
                        this->mem[current_word] = op1;
                        break;
                    case SEG: {
                        current_word = this->mem[++this->reg[IP]];
                        current_word += this->reg[BP];
                        if(current_word >= this->mem.size()) throw "INVALID MEM ADDR";
                        this->mem[current_word] = op1;
                        break;
                    }
                    default:
                        throw "INVALID INSTRUCTION";
                }
                break;
            }

            default:
                break;
        }
        this->reg[IP]++;
    }
}

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