#ifndef __PL0_INSTRUCTION__
#define __PL0_INSTRUCTION__

typedef unsigned int WORD;

#define PUSH  0x1000u
#define POP   0x2000u

#define READW  0x3000u
#define READB  0x3001u
#define READF  0x3002u

#define WRITEW 0x4000u
#define WRITEB 0x4001u
#define WRITEF 0x4002u

#define CMPW   0x5000u
#define CMPB   0x5001u
#define CMPF   0x5002u

#define JMP    0xA000u
#define JG     0xA001u
#define JL     0xA002u
#define JE     0xA003u
#define JNE    0xA004u
#define JEG    0xA005u
#define JEL    0xA006u
#define JODD   0xA007u


#define ADDW   0x6000u
#define SUBW   0x6001u
#define MULW   0x6002u
#define DIVW   0x6003u

#define ADDB   0x7000u
#define SUBB   0x7001u
#define MULB   0x7002u
#define DIVB   0x7003u

#define ADDF   0x8000u
#define SUBF   0x8001u
#define MULF   0x8002u
#define DIVF   0x8003u

#define CVTW   0x9000u
#define CVTF   0x9001u

#define HALT   0xFFFFu

#define CALL   0xFF02u
#define RET    0xFF01u

#define MOV    0xE000u

#define IP     0x00000000u
#define BP     0x00000001u
#define SP     0x00000002u
#define RA     0x00000003u
#define RB     0x00000004u
#define RR     0x00000005u
#define FA     0x00000006u
#define FB     0x00000007u
#define FR     0x00000008u
#define SR     0x00000009u
#define MAXREG 0x0000000Au

#define HALT 0xFFFFu

#define IMM 0x00u
#define REG 0x01u
#define MEM 0x10u
#define SEG 0x11u
#define EMP 0xFFu

WORD prepare_inst(WORD opcode, WORD op1, WORD op2);
WORD int_to_word(int i);
WORD char_to_word(char i);
WORD float_to_word(char i);


#endif