/* Minimal freestanding stand-in for <stdlib.h>, used only by the WASM build. */
#ifndef FTEC_WASM_STDLIB_H
#define FTEC_WASM_STDLIB_H
#define abort() __builtin_trap()
#endif
