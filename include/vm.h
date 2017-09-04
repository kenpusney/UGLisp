
#ifndef __VM_H
#define __VM_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

enum opcode_t
{
    MC_NOP = 0x00,
    MC_PUSH = 0x10,
    MC_POP,
    MC_STACK_REF,
    MC_PROTOCOL,
    MC_INVOKE,
    MC_GLOBAL,
    MC_JMP,
    MC_RET,
    MC_FALSE,
};

typedef struct operation_t
{
    enum opcode_t opcode;
    MObject *params;
    struct operation_t *next;
} * Operations;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //__VM_H
