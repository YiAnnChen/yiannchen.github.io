/* Minimal freestanding stand-in for <stdio.h>, used only by the WASM build.
 * legacy.c (FTEC_NATIVE) uses stdio for exactly one call:
 *   fprintf(stderr, "FTEC error %d\n", error_id);
 * which is redirected to the JavaScript host. */
#ifndef FTEC_WASM_STDIO_H
#define FTEC_WASM_STDIO_H
void ftec_legacy_error(int code);
#define stderr 0
#define fprintf(stream, format, code) ftec_legacy_error(code)
#endif
