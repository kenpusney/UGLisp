
#ifndef _MCODE_H
#define _MCODE_H

typedef enum MISSION_OPCODE {
    MC_PUSH = 0x10,
    MC_POP,
    MC_STACK_REF,
    MC_PROTOCOL,
    MC_APPLY,
    MC_CALL,
    MC_GLOBAL,
    MC_JMP,
    MC_RET,
    MC_FALSE,
} MISSION_OPCODE;

#endif //_MCODE_H
