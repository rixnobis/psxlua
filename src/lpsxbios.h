/*
** BIOS calls for the PlayStation target.
** Each call goes through a two-instruction thunk, `j 0xa0` with t1 set in its
** delay slot, emitted in every file that includes this header as a weak symbol
** in its own COMDAT section, so the linker keeps one copy of each. To the
** compiler the thunk is a plain function: t1 cannot be reused before the jump,
** and the BIOS returns straight to the caller.
*/

#ifndef lpsxbios_h
#define lpsxbios_h

#include <stddef.h>

#define LUAI_PSX_BIOS_THUNK(name, table, number) \
    __asm__(".pushsection .text.__psxlua_bios_" #name ",\"axG\",@progbits,__psxlua_bios_" #name ",comdat\n" \
            ".weak __psxlua_bios_" #name "\n" \
            ".type __psxlua_bios_" #name ", @function\n" \
            ".set push\n.set noreorder\n" \
            "__psxlua_bios_" #name ":\n" \
            "    j " #table "\n" \
            "    li $t1, " #number "\n" \
            ".set pop\n" \
            ".size __psxlua_bios_" #name ", . - __psxlua_bios_" #name "\n" \
            ".popsection\n");

#ifdef __cplusplus
#define LUAI_PSX_BIOS_EXTERN extern "C"
#else
#define LUAI_PSX_BIOS_EXTERN extern
#endif

#endif
