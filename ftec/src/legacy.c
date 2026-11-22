/* Steane [[7,1,3]], r+s<=1. Generated fixed full-history flag decoder.
 * q0..q6=data, q7=syndrome, q8=flag. Global Pauli phase is ignored.
 * FTEC_TASK: 0=both, 1=single-execution residual, 2=pair property.
 * FTEC_BROKEN_DECODER: deliberate mutation (normal correction = identity).
 * No headers are needed for CPAchecker. See README_zh.md for scope.
 */
#ifndef FTEC_TASK
#define FTEC_TASK 0
#endif
#ifndef FTEC_BROKEN_DECODER
#define FTEC_BROKEN_DECODER 0
#endif
#define CAP 8
#ifdef FTEC_NATIVE
#include <stdio.h>
#include <stdlib.h>
#else
extern unsigned int __VERIFIER_nondet_uint(void);
extern void __VERIFIER_error(void) __attribute__((noreturn));
#endif

/* Error IDs: 1=capacity; 2=budget; 3=missing decoder entry;
 * 4=residual bound; 5=pairwise logical ambiguity. */
void require(int condition, int error_id) {
    if (!condition) {
#ifdef FTEC_NATIVE
        fprintf(stderr, "FTEC error %d\n", error_id);
        abort();
#else
        (void)error_id;
        goto ERROR;
        ERROR: __VERIFIER_error();
#endif
    }
}
typedef struct { unsigned int x, z; } Pauli;
typedef struct {
    unsigned int mode, q, a, round, k, op, p;
} Input;
typedef struct {
    Pauli e;
    unsigned int r, s, n, branch;
    unsigned int history[CAP]; /* syndrome bits 0..5; flag bits 6..11 */
} Result;
typedef struct {
    unsigned int n, history[CAP], x, z;
} FlagEntry;
static const unsigned int H[3] = {120u, 102u, 85u};
static const FlagEntry FLAG_TABLE[] = {
    {3u, {64u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {65u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {72u, 8u, 8u, 0u, 0u, 0u, 0u, 0u}, 0u, 112u},
    {3u, {73u, 8u, 8u, 0u, 0u, 0u, 0u, 0u}, 0u, 112u},
    {3u, {96u, 32u, 32u, 0u, 0u, 0u, 0u, 0u}, 0u, 96u},
    {3u, {100u, 37u, 37u, 0u, 0u, 0u, 0u, 0u}, 16u, 96u},
    {3u, {76u, 13u, 13u, 0u, 0u, 0u, 0u, 0u}, 16u, 112u},
    {3u, {97u, 32u, 32u, 0u, 0u, 0u, 0u, 0u}, 0u, 96u},
    {3u, {101u, 37u, 37u, 0u, 0u, 0u, 0u, 0u}, 16u, 96u},
    {3u, {77u, 13u, 13u, 0u, 0u, 0u, 0u, 0u}, 16u, 112u},
    {3u, {120u, 56u, 56u, 0u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {3u, {122u, 59u, 59u, 0u, 0u, 0u, 0u, 0u}, 32u, 64u},
    {3u, {98u, 35u, 35u, 0u, 0u, 0u, 0u, 0u}, 32u, 96u},
    {3u, {121u, 56u, 56u, 0u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {3u, {123u, 59u, 59u, 0u, 0u, 0u, 0u, 0u}, 32u, 64u},
    {3u, {99u, 35u, 35u, 0u, 0u, 0u, 0u, 0u}, 32u, 96u},
    {3u, {128u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {130u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {144u, 16u, 16u, 0u, 0u, 0u, 0u, 0u}, 0u, 100u},
    {3u, {146u, 16u, 16u, 0u, 0u, 0u, 0u, 0u}, 0u, 100u},
    {3u, {160u, 32u, 32u, 0u, 0u, 0u, 0u, 0u}, 0u, 96u},
    {3u, {164u, 38u, 38u, 0u, 0u, 0u, 0u, 0u}, 4u, 96u},
    {3u, {148u, 22u, 22u, 0u, 0u, 0u, 0u, 0u}, 4u, 100u},
    {3u, {162u, 32u, 32u, 0u, 0u, 0u, 0u, 0u}, 0u, 96u},
    {3u, {166u, 38u, 38u, 0u, 0u, 0u, 0u, 0u}, 4u, 96u},
    {3u, {150u, 22u, 22u, 0u, 0u, 0u, 0u, 0u}, 4u, 100u},
    {3u, {184u, 56u, 56u, 0u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {3u, {184u, 59u, 59u, 0u, 0u, 0u, 0u, 0u}, 32u, 64u},
    {3u, {160u, 35u, 35u, 0u, 0u, 0u, 0u, 0u}, 32u, 96u},
    {3u, {186u, 56u, 56u, 0u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {3u, {186u, 59u, 59u, 0u, 0u, 0u, 0u, 0u}, 32u, 64u},
    {3u, {162u, 35u, 35u, 0u, 0u, 0u, 0u, 0u}, 32u, 96u},
    {3u, {256u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {260u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {288u, 32u, 32u, 0u, 0u, 0u, 0u, 0u}, 0u, 84u},
    {3u, {292u, 32u, 32u, 0u, 0u, 0u, 0u, 0u}, 0u, 84u},
    {3u, {272u, 16u, 16u, 0u, 0u, 0u, 0u, 0u}, 0u, 80u},
    {3u, {272u, 22u, 22u, 0u, 0u, 0u, 0u, 0u}, 4u, 80u},
    {3u, {288u, 38u, 38u, 0u, 0u, 0u, 0u, 0u}, 4u, 84u},
    {3u, {276u, 16u, 16u, 0u, 0u, 0u, 0u, 0u}, 0u, 80u},
    {3u, {276u, 22u, 22u, 0u, 0u, 0u, 0u, 0u}, 4u, 80u},
    {3u, {292u, 38u, 38u, 0u, 0u, 0u, 0u, 0u}, 4u, 84u},
    {3u, {312u, 56u, 56u, 0u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {3u, {312u, 61u, 61u, 0u, 0u, 0u, 0u, 0u}, 16u, 64u},
    {3u, {272u, 21u, 21u, 0u, 0u, 0u, 0u, 0u}, 16u, 80u},
    {3u, {316u, 56u, 56u, 0u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {3u, {316u, 61u, 61u, 0u, 0u, 0u, 0u, 0u}, 16u, 64u},
    {3u, {276u, 21u, 21u, 0u, 0u, 0u, 0u, 0u}, 16u, 80u},
    {3u, {512u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {512u, 1u, 1u, 0u, 0u, 0u, 0u, 0u}, 112u, 0u},
    {3u, {520u, 1u, 1u, 0u, 0u, 0u, 0u, 0u}, 112u, 0u},
    {3u, {520u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {512u, 4u, 4u, 0u, 0u, 0u, 0u, 0u}, 96u, 0u},
    {3u, {520u, 4u, 4u, 0u, 0u, 0u, 0u, 0u}, 96u, 0u},
    {3u, {544u, 44u, 44u, 0u, 0u, 0u, 0u, 0u}, 96u, 16u},
    {3u, {552u, 44u, 44u, 0u, 0u, 0u, 0u, 0u}, 96u, 16u},
    {3u, {544u, 41u, 41u, 0u, 0u, 0u, 0u, 0u}, 112u, 16u},
    {3u, {552u, 41u, 41u, 0u, 0u, 0u, 0u, 0u}, 112u, 16u},
    {3u, {512u, 7u, 7u, 0u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {3u, {520u, 7u, 7u, 0u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {3u, {528u, 31u, 31u, 0u, 0u, 0u, 0u, 0u}, 64u, 32u},
    {3u, {536u, 31u, 31u, 0u, 0u, 0u, 0u, 0u}, 64u, 32u},
    {3u, {528u, 28u, 28u, 0u, 0u, 0u, 0u, 0u}, 96u, 32u},
    {3u, {536u, 28u, 28u, 0u, 0u, 0u, 0u, 0u}, 96u, 32u},
    {3u, {1024u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {1024u, 2u, 2u, 0u, 0u, 0u, 0u, 0u}, 100u, 0u},
    {3u, {1040u, 2u, 2u, 0u, 0u, 0u, 0u, 0u}, 100u, 0u},
    {3u, {1040u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {1024u, 4u, 4u, 0u, 0u, 0u, 0u, 0u}, 96u, 0u},
    {3u, {1040u, 4u, 4u, 0u, 0u, 0u, 0u, 0u}, 96u, 0u},
    {3u, {1056u, 52u, 52u, 0u, 0u, 0u, 0u, 0u}, 96u, 4u},
    {3u, {1072u, 52u, 52u, 0u, 0u, 0u, 0u, 0u}, 96u, 4u},
    {3u, {1056u, 50u, 50u, 0u, 0u, 0u, 0u, 0u}, 100u, 4u},
    {3u, {1072u, 50u, 50u, 0u, 0u, 0u, 0u, 0u}, 100u, 4u},
    {3u, {1024u, 7u, 7u, 0u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {3u, {1040u, 7u, 7u, 0u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {3u, {1024u, 31u, 31u, 0u, 0u, 0u, 0u, 0u}, 64u, 32u},
    {3u, {1040u, 31u, 31u, 0u, 0u, 0u, 0u, 0u}, 64u, 32u},
    {3u, {1024u, 28u, 28u, 0u, 0u, 0u, 0u, 0u}, 96u, 32u},
    {3u, {1040u, 28u, 28u, 0u, 0u, 0u, 0u, 0u}, 96u, 32u},
    {3u, {2048u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {2048u, 4u, 4u, 0u, 0u, 0u, 0u, 0u}, 84u, 0u},
    {3u, {2080u, 4u, 4u, 0u, 0u, 0u, 0u, 0u}, 84u, 0u},
    {3u, {2080u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {3u, {2048u, 2u, 2u, 0u, 0u, 0u, 0u, 0u}, 80u, 0u},
    {3u, {2080u, 2u, 2u, 0u, 0u, 0u, 0u, 0u}, 80u, 0u},
    {3u, {2048u, 50u, 50u, 0u, 0u, 0u, 0u, 0u}, 80u, 4u},
    {3u, {2080u, 50u, 50u, 0u, 0u, 0u, 0u, 0u}, 80u, 4u},
    {3u, {2048u, 52u, 52u, 0u, 0u, 0u, 0u, 0u}, 84u, 4u},
    {3u, {2080u, 52u, 52u, 0u, 0u, 0u, 0u, 0u}, 84u, 4u},
    {3u, {2048u, 7u, 7u, 0u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {3u, {2080u, 7u, 7u, 0u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {3u, {2048u, 47u, 47u, 0u, 0u, 0u, 0u, 0u}, 64u, 16u},
    {3u, {2080u, 47u, 47u, 0u, 0u, 0u, 0u, 0u}, 64u, 16u},
    {3u, {2048u, 42u, 42u, 0u, 0u, 0u, 0u, 0u}, 80u, 16u},
    {3u, {2080u, 42u, 42u, 0u, 0u, 0u, 0u, 0u}, 80u, 16u},
    {4u, {0u, 64u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 65u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 72u, 8u, 8u, 0u, 0u, 0u, 0u}, 0u, 112u},
    {4u, {0u, 73u, 8u, 8u, 0u, 0u, 0u, 0u}, 0u, 112u},
    {4u, {0u, 96u, 32u, 32u, 0u, 0u, 0u, 0u}, 0u, 96u},
    {4u, {0u, 100u, 37u, 37u, 0u, 0u, 0u, 0u}, 16u, 96u},
    {4u, {0u, 76u, 13u, 13u, 0u, 0u, 0u, 0u}, 16u, 112u},
    {4u, {0u, 97u, 32u, 32u, 0u, 0u, 0u, 0u}, 0u, 96u},
    {4u, {0u, 101u, 37u, 37u, 0u, 0u, 0u, 0u}, 16u, 96u},
    {4u, {0u, 77u, 13u, 13u, 0u, 0u, 0u, 0u}, 16u, 112u},
    {4u, {0u, 120u, 56u, 56u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {4u, {0u, 122u, 59u, 59u, 0u, 0u, 0u, 0u}, 32u, 64u},
    {4u, {0u, 98u, 35u, 35u, 0u, 0u, 0u, 0u}, 32u, 96u},
    {4u, {0u, 121u, 56u, 56u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {4u, {0u, 123u, 59u, 59u, 0u, 0u, 0u, 0u}, 32u, 64u},
    {4u, {0u, 99u, 35u, 35u, 0u, 0u, 0u, 0u}, 32u, 96u},
    {4u, {0u, 128u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 130u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 144u, 16u, 16u, 0u, 0u, 0u, 0u}, 0u, 100u},
    {4u, {0u, 146u, 16u, 16u, 0u, 0u, 0u, 0u}, 0u, 100u},
    {4u, {0u, 160u, 32u, 32u, 0u, 0u, 0u, 0u}, 0u, 96u},
    {4u, {0u, 164u, 38u, 38u, 0u, 0u, 0u, 0u}, 4u, 96u},
    {4u, {0u, 148u, 22u, 22u, 0u, 0u, 0u, 0u}, 4u, 100u},
    {4u, {0u, 162u, 32u, 32u, 0u, 0u, 0u, 0u}, 0u, 96u},
    {4u, {0u, 166u, 38u, 38u, 0u, 0u, 0u, 0u}, 4u, 96u},
    {4u, {0u, 150u, 22u, 22u, 0u, 0u, 0u, 0u}, 4u, 100u},
    {4u, {0u, 184u, 56u, 56u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {4u, {0u, 184u, 59u, 59u, 0u, 0u, 0u, 0u}, 32u, 64u},
    {4u, {0u, 160u, 35u, 35u, 0u, 0u, 0u, 0u}, 32u, 96u},
    {4u, {0u, 186u, 56u, 56u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {4u, {0u, 186u, 59u, 59u, 0u, 0u, 0u, 0u}, 32u, 64u},
    {4u, {0u, 162u, 35u, 35u, 0u, 0u, 0u, 0u}, 32u, 96u},
    {4u, {0u, 256u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 260u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 288u, 32u, 32u, 0u, 0u, 0u, 0u}, 0u, 84u},
    {4u, {0u, 292u, 32u, 32u, 0u, 0u, 0u, 0u}, 0u, 84u},
    {4u, {0u, 272u, 16u, 16u, 0u, 0u, 0u, 0u}, 0u, 80u},
    {4u, {0u, 272u, 22u, 22u, 0u, 0u, 0u, 0u}, 4u, 80u},
    {4u, {0u, 288u, 38u, 38u, 0u, 0u, 0u, 0u}, 4u, 84u},
    {4u, {0u, 276u, 16u, 16u, 0u, 0u, 0u, 0u}, 0u, 80u},
    {4u, {0u, 276u, 22u, 22u, 0u, 0u, 0u, 0u}, 4u, 80u},
    {4u, {0u, 292u, 38u, 38u, 0u, 0u, 0u, 0u}, 4u, 84u},
    {4u, {0u, 312u, 56u, 56u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {4u, {0u, 312u, 61u, 61u, 0u, 0u, 0u, 0u}, 16u, 64u},
    {4u, {0u, 272u, 21u, 21u, 0u, 0u, 0u, 0u}, 16u, 80u},
    {4u, {0u, 316u, 56u, 56u, 0u, 0u, 0u, 0u}, 0u, 64u},
    {4u, {0u, 316u, 61u, 61u, 0u, 0u, 0u, 0u}, 16u, 64u},
    {4u, {0u, 276u, 21u, 21u, 0u, 0u, 0u, 0u}, 16u, 80u},
    {4u, {0u, 512u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 512u, 1u, 1u, 0u, 0u, 0u, 0u}, 112u, 0u},
    {4u, {0u, 520u, 1u, 1u, 0u, 0u, 0u, 0u}, 112u, 0u},
    {4u, {0u, 520u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 512u, 4u, 4u, 0u, 0u, 0u, 0u}, 96u, 0u},
    {4u, {0u, 520u, 4u, 4u, 0u, 0u, 0u, 0u}, 96u, 0u},
    {4u, {0u, 544u, 44u, 44u, 0u, 0u, 0u, 0u}, 96u, 16u},
    {4u, {0u, 552u, 44u, 44u, 0u, 0u, 0u, 0u}, 96u, 16u},
    {4u, {0u, 544u, 41u, 41u, 0u, 0u, 0u, 0u}, 112u, 16u},
    {4u, {0u, 552u, 41u, 41u, 0u, 0u, 0u, 0u}, 112u, 16u},
    {4u, {0u, 512u, 7u, 7u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {4u, {0u, 520u, 7u, 7u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {4u, {0u, 528u, 31u, 31u, 0u, 0u, 0u, 0u}, 64u, 32u},
    {4u, {0u, 536u, 31u, 31u, 0u, 0u, 0u, 0u}, 64u, 32u},
    {4u, {0u, 528u, 28u, 28u, 0u, 0u, 0u, 0u}, 96u, 32u},
    {4u, {0u, 536u, 28u, 28u, 0u, 0u, 0u, 0u}, 96u, 32u},
    {4u, {0u, 1024u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 1024u, 2u, 2u, 0u, 0u, 0u, 0u}, 100u, 0u},
    {4u, {0u, 1040u, 2u, 2u, 0u, 0u, 0u, 0u}, 100u, 0u},
    {4u, {0u, 1040u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 1024u, 4u, 4u, 0u, 0u, 0u, 0u}, 96u, 0u},
    {4u, {0u, 1040u, 4u, 4u, 0u, 0u, 0u, 0u}, 96u, 0u},
    {4u, {0u, 1056u, 52u, 52u, 0u, 0u, 0u, 0u}, 96u, 4u},
    {4u, {0u, 1072u, 52u, 52u, 0u, 0u, 0u, 0u}, 96u, 4u},
    {4u, {0u, 1056u, 50u, 50u, 0u, 0u, 0u, 0u}, 100u, 4u},
    {4u, {0u, 1072u, 50u, 50u, 0u, 0u, 0u, 0u}, 100u, 4u},
    {4u, {0u, 1024u, 7u, 7u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {4u, {0u, 1040u, 7u, 7u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {4u, {0u, 1024u, 31u, 31u, 0u, 0u, 0u, 0u}, 64u, 32u},
    {4u, {0u, 1040u, 31u, 31u, 0u, 0u, 0u, 0u}, 64u, 32u},
    {4u, {0u, 1024u, 28u, 28u, 0u, 0u, 0u, 0u}, 96u, 32u},
    {4u, {0u, 1040u, 28u, 28u, 0u, 0u, 0u, 0u}, 96u, 32u},
    {4u, {0u, 2048u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 2048u, 4u, 4u, 0u, 0u, 0u, 0u}, 84u, 0u},
    {4u, {0u, 2080u, 4u, 4u, 0u, 0u, 0u, 0u}, 84u, 0u},
    {4u, {0u, 2080u, 0u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {4u, {0u, 2048u, 2u, 2u, 0u, 0u, 0u, 0u}, 80u, 0u},
    {4u, {0u, 2080u, 2u, 2u, 0u, 0u, 0u, 0u}, 80u, 0u},
    {4u, {0u, 2048u, 50u, 50u, 0u, 0u, 0u, 0u}, 80u, 4u},
    {4u, {0u, 2080u, 50u, 50u, 0u, 0u, 0u, 0u}, 80u, 4u},
    {4u, {0u, 2048u, 52u, 52u, 0u, 0u, 0u, 0u}, 84u, 4u},
    {4u, {0u, 2080u, 52u, 52u, 0u, 0u, 0u, 0u}, 84u, 4u},
    {4u, {0u, 2048u, 7u, 7u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {4u, {0u, 2080u, 7u, 7u, 0u, 0u, 0u, 0u}, 64u, 0u},
    {4u, {0u, 2048u, 47u, 47u, 0u, 0u, 0u, 0u}, 64u, 16u},
    {4u, {0u, 2080u, 47u, 47u, 0u, 0u, 0u, 0u}, 64u, 16u},
    {4u, {0u, 2048u, 42u, 42u, 0u, 0u, 0u, 0u}, 80u, 16u},
    {4u, {0u, 2080u, 42u, 42u, 0u, 0u, 0u, 0u}, 80u, 16u},
    {5u, {0u, 0u, 64u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 65u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 72u, 8u, 8u, 0u, 0u, 0u}, 0u, 112u},
    {5u, {0u, 0u, 73u, 8u, 8u, 0u, 0u, 0u}, 0u, 112u},
    {5u, {0u, 0u, 96u, 32u, 32u, 0u, 0u, 0u}, 0u, 96u},
    {5u, {0u, 0u, 100u, 37u, 37u, 0u, 0u, 0u}, 16u, 96u},
    {5u, {0u, 0u, 76u, 13u, 13u, 0u, 0u, 0u}, 16u, 112u},
    {5u, {0u, 0u, 97u, 32u, 32u, 0u, 0u, 0u}, 0u, 96u},
    {5u, {0u, 0u, 101u, 37u, 37u, 0u, 0u, 0u}, 16u, 96u},
    {5u, {0u, 0u, 77u, 13u, 13u, 0u, 0u, 0u}, 16u, 112u},
    {5u, {0u, 0u, 120u, 56u, 56u, 0u, 0u, 0u}, 0u, 64u},
    {5u, {0u, 0u, 122u, 59u, 59u, 0u, 0u, 0u}, 32u, 64u},
    {5u, {0u, 0u, 98u, 35u, 35u, 0u, 0u, 0u}, 32u, 96u},
    {5u, {0u, 0u, 121u, 56u, 56u, 0u, 0u, 0u}, 0u, 64u},
    {5u, {0u, 0u, 123u, 59u, 59u, 0u, 0u, 0u}, 32u, 64u},
    {5u, {0u, 0u, 99u, 35u, 35u, 0u, 0u, 0u}, 32u, 96u},
    {5u, {0u, 0u, 128u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 130u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 144u, 16u, 16u, 0u, 0u, 0u}, 0u, 100u},
    {5u, {0u, 0u, 146u, 16u, 16u, 0u, 0u, 0u}, 0u, 100u},
    {5u, {0u, 0u, 160u, 32u, 32u, 0u, 0u, 0u}, 0u, 96u},
    {5u, {0u, 0u, 164u, 38u, 38u, 0u, 0u, 0u}, 4u, 96u},
    {5u, {0u, 0u, 148u, 22u, 22u, 0u, 0u, 0u}, 4u, 100u},
    {5u, {0u, 0u, 162u, 32u, 32u, 0u, 0u, 0u}, 0u, 96u},
    {5u, {0u, 0u, 166u, 38u, 38u, 0u, 0u, 0u}, 4u, 96u},
    {5u, {0u, 0u, 150u, 22u, 22u, 0u, 0u, 0u}, 4u, 100u},
    {5u, {0u, 0u, 184u, 56u, 56u, 0u, 0u, 0u}, 0u, 64u},
    {5u, {0u, 0u, 184u, 59u, 59u, 0u, 0u, 0u}, 32u, 64u},
    {5u, {0u, 0u, 160u, 35u, 35u, 0u, 0u, 0u}, 32u, 96u},
    {5u, {0u, 0u, 186u, 56u, 56u, 0u, 0u, 0u}, 0u, 64u},
    {5u, {0u, 0u, 186u, 59u, 59u, 0u, 0u, 0u}, 32u, 64u},
    {5u, {0u, 0u, 162u, 35u, 35u, 0u, 0u, 0u}, 32u, 96u},
    {5u, {0u, 0u, 256u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 260u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 288u, 32u, 32u, 0u, 0u, 0u}, 0u, 84u},
    {5u, {0u, 0u, 292u, 32u, 32u, 0u, 0u, 0u}, 0u, 84u},
    {5u, {0u, 0u, 272u, 16u, 16u, 0u, 0u, 0u}, 0u, 80u},
    {5u, {0u, 0u, 272u, 22u, 22u, 0u, 0u, 0u}, 4u, 80u},
    {5u, {0u, 0u, 288u, 38u, 38u, 0u, 0u, 0u}, 4u, 84u},
    {5u, {0u, 0u, 276u, 16u, 16u, 0u, 0u, 0u}, 0u, 80u},
    {5u, {0u, 0u, 276u, 22u, 22u, 0u, 0u, 0u}, 4u, 80u},
    {5u, {0u, 0u, 292u, 38u, 38u, 0u, 0u, 0u}, 4u, 84u},
    {5u, {0u, 0u, 312u, 56u, 56u, 0u, 0u, 0u}, 0u, 64u},
    {5u, {0u, 0u, 312u, 61u, 61u, 0u, 0u, 0u}, 16u, 64u},
    {5u, {0u, 0u, 272u, 21u, 21u, 0u, 0u, 0u}, 16u, 80u},
    {5u, {0u, 0u, 316u, 56u, 56u, 0u, 0u, 0u}, 0u, 64u},
    {5u, {0u, 0u, 316u, 61u, 61u, 0u, 0u, 0u}, 16u, 64u},
    {5u, {0u, 0u, 276u, 21u, 21u, 0u, 0u, 0u}, 16u, 80u},
    {5u, {0u, 0u, 512u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 512u, 1u, 1u, 0u, 0u, 0u}, 112u, 0u},
    {5u, {0u, 0u, 520u, 1u, 1u, 0u, 0u, 0u}, 112u, 0u},
    {5u, {0u, 0u, 520u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 512u, 4u, 4u, 0u, 0u, 0u}, 96u, 0u},
    {5u, {0u, 0u, 520u, 4u, 4u, 0u, 0u, 0u}, 96u, 0u},
    {5u, {0u, 0u, 544u, 44u, 44u, 0u, 0u, 0u}, 96u, 16u},
    {5u, {0u, 0u, 552u, 44u, 44u, 0u, 0u, 0u}, 96u, 16u},
    {5u, {0u, 0u, 544u, 41u, 41u, 0u, 0u, 0u}, 112u, 16u},
    {5u, {0u, 0u, 552u, 41u, 41u, 0u, 0u, 0u}, 112u, 16u},
    {5u, {0u, 0u, 512u, 7u, 7u, 0u, 0u, 0u}, 64u, 0u},
    {5u, {0u, 0u, 520u, 7u, 7u, 0u, 0u, 0u}, 64u, 0u},
    {5u, {0u, 0u, 528u, 31u, 31u, 0u, 0u, 0u}, 64u, 32u},
    {5u, {0u, 0u, 536u, 31u, 31u, 0u, 0u, 0u}, 64u, 32u},
    {5u, {0u, 0u, 528u, 28u, 28u, 0u, 0u, 0u}, 96u, 32u},
    {5u, {0u, 0u, 536u, 28u, 28u, 0u, 0u, 0u}, 96u, 32u},
    {5u, {0u, 0u, 1024u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 1024u, 2u, 2u, 0u, 0u, 0u}, 100u, 0u},
    {5u, {0u, 0u, 1040u, 2u, 2u, 0u, 0u, 0u}, 100u, 0u},
    {5u, {0u, 0u, 1040u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 1024u, 4u, 4u, 0u, 0u, 0u}, 96u, 0u},
    {5u, {0u, 0u, 1040u, 4u, 4u, 0u, 0u, 0u}, 96u, 0u},
    {5u, {0u, 0u, 1056u, 52u, 52u, 0u, 0u, 0u}, 96u, 4u},
    {5u, {0u, 0u, 1072u, 52u, 52u, 0u, 0u, 0u}, 96u, 4u},
    {5u, {0u, 0u, 1056u, 50u, 50u, 0u, 0u, 0u}, 100u, 4u},
    {5u, {0u, 0u, 1072u, 50u, 50u, 0u, 0u, 0u}, 100u, 4u},
    {5u, {0u, 0u, 1024u, 7u, 7u, 0u, 0u, 0u}, 64u, 0u},
    {5u, {0u, 0u, 1040u, 7u, 7u, 0u, 0u, 0u}, 64u, 0u},
    {5u, {0u, 0u, 1024u, 31u, 31u, 0u, 0u, 0u}, 64u, 32u},
    {5u, {0u, 0u, 1040u, 31u, 31u, 0u, 0u, 0u}, 64u, 32u},
    {5u, {0u, 0u, 1024u, 28u, 28u, 0u, 0u, 0u}, 96u, 32u},
    {5u, {0u, 0u, 1040u, 28u, 28u, 0u, 0u, 0u}, 96u, 32u},
    {5u, {0u, 0u, 2048u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 2048u, 4u, 4u, 0u, 0u, 0u}, 84u, 0u},
    {5u, {0u, 0u, 2080u, 4u, 4u, 0u, 0u, 0u}, 84u, 0u},
    {5u, {0u, 0u, 2080u, 0u, 0u, 0u, 0u, 0u}, 0u, 0u},
    {5u, {0u, 0u, 2048u, 2u, 2u, 0u, 0u, 0u}, 80u, 0u},
    {5u, {0u, 0u, 2080u, 2u, 2u, 0u, 0u, 0u}, 80u, 0u},
    {5u, {0u, 0u, 2048u, 50u, 50u, 0u, 0u, 0u}, 80u, 4u},
    {5u, {0u, 0u, 2080u, 50u, 50u, 0u, 0u, 0u}, 80u, 4u},
    {5u, {0u, 0u, 2048u, 52u, 52u, 0u, 0u, 0u}, 84u, 4u},
    {5u, {0u, 0u, 2080u, 52u, 52u, 0u, 0u, 0u}, 84u, 4u},
    {5u, {0u, 0u, 2048u, 7u, 7u, 0u, 0u, 0u}, 64u, 0u},
    {5u, {0u, 0u, 2080u, 7u, 7u, 0u, 0u, 0u}, 64u, 0u},
    {5u, {0u, 0u, 2048u, 47u, 47u, 0u, 0u, 0u}, 64u, 16u},
    {5u, {0u, 0u, 2080u, 47u, 47u, 0u, 0u, 0u}, 64u, 16u},
    {5u, {0u, 0u, 2048u, 42u, 42u, 0u, 0u, 0u}, 80u, 16u},
    {5u, {0u, 0u, 2080u, 42u, 42u, 0u, 0u, 0u}, 80u, 16u},
};
static const unsigned int FLAG_COUNT = 288u;

unsigned int parity(unsigned int v) {
    unsigned int p=0u, j;
    for (j=0u; j<7u; j++) p ^= (v>>j)&1u;
    return p;
}
unsigned int weight(Pauli e) {
    unsigned int w=0u, j;
    for (j=0u; j<7u; j++) w += ((e.x|e.z)>>j)&1u;
    return w;
}
Pauli multiply(Pauli a, Pauli b) {
    Pauli p; p.x=a.x^b.x; p.z=a.z^b.z; return p;
}
unsigned int syndrome(Pauli e) {
    unsigned int v=0u, j;
    for (j=0u; j<3u; j++) {
        v |= parity(e.x&H[j])<<j;
        v |= parity(e.z&H[j])<<(j+3u);
    }
    return v;
}
Pauli stabilizer(unsigned int mask) {
    Pauli g={0u,0u}; unsigned int j;
    for (j=0u; j<3u; j++) {
        if ((mask>>j)&1u) g.x ^= H[j];
        if ((mask>>(j+3u))&1u) g.z ^= H[j];
    }
    return g;
}
unsigned int min_weight(Pauli p) {
    unsigned int best=7u, mask, w;
    for (mask=0u; mask<64u; mask++) {
        w=weight(multiply(p,stabilizer(mask)));
        if (w<best) best=w;
    }
    return best;
}
int in_stabilizer(Pauli p) {
    unsigned int mask; Pauli g;
    for (mask=0u; mask<64u; mask++) {
        g=stabilizer(mask);
        if (p.x==g.x && p.z==g.z) return 1;
    }
    return 0;
}
void cnot(Pauli *e, unsigned int control, unsigned int target) {
    if ((e->x>>control)&1u) e->x ^= 1u<<target;
    if ((e->z>>target)&1u) e->z ^= 1u<<control;
}
void insert_single(Pauli *e, unsigned int q, unsigned int a) {
    if (a&1u) e->x ^= 1u<<q;
    if (a&2u) e->z ^= 1u<<q;
}
/* Invalid nondeterministic choices are filtered in main before run_model.
 * mode 0: clean; mode 1: one initial Pauli; mode 2: one circuit fault.
 * First circuit fault can only be in baseline rounds 1..3. */
int valid_input(Input f) {
    if (f.mode>2u) return 0;
    if (f.mode==1u) return f.q<7u && f.a>=1u && f.a<=3u;
    if (f.mode==2u) {
        if (f.round<1u || f.round>3u || f.k>=6u || f.op>=10u)
            return 0;
        if (f.op>=2u && f.op<=7u) return f.p>=1u && f.p<=15u;
        return f.p==1u;
    }
    return 1;
}
/* All preparations reset to the appropriate ideal eigenstate. The Pauli
 * frame starts with no ancilla errors, as in the Python reference. */
unsigned int measure_generator(Pauli *data, Input f,
                               unsigned int rr, unsigned int k,
                               unsigned int *fault_count) {
    Pauli e=*data;
    unsigned int qs[4], count=0u, j, op, c=0u, t=0u, q, a, basis_z;
    unsigned int out=0u;
    for (j=0u; j<7u; j++) if ((H[k%3u]>>j)&1u) qs[count++]=j;
    for (op=0u; op<10u; op++) {
        if (op>=2u && op<=7u) {
            if (op==2u) c=qs[0];
            else if (op==3u || op==6u) c=8u;
            else if (op==4u) c=qs[1];
            else if (op==5u) c=qs[2];
            else c=qs[3];
            t=7u;
            if (k>=3u) { j=c; c=t; t=j; }
            cnot(&e,c,t);
        }
        if (f.mode==2u && f.round==rr && f.k==k && f.op==op) {
            (*fault_count)++;
            if (op>=2u && op<=7u) {
                insert_single(&e,c,f.p&3u);
                insert_single(&e,t,(f.p>>2u)&3u);
            } else {
                q=(op==0u || op==8u)?7u:8u;
                basis_z=((q==7u)==(k<3u));
                a=basis_z?1u:2u;
                insert_single(&e,q,a);
            }
        }
        if (op>=8u) {
            q=(op==8u)?7u:8u;
            basis_z=((q==7u)==(k<3u));
            out |= (((basis_z?e.x:e.z)>>q)&1u)<<(op-8u);
        }
    }
    data->x=e.x&127u; data->z=e.z&127u;
    return out; /* bit0=syndrome, bit1=flag */
}
Result run_model(Input f) {
    Result r={0};
    unsigned int previous=0u, equal_count=0u, after=0u;
    unsigned int rr=1u, k, outcome, v, flags;
    if (f.mode==1u) { insert_single(&r.e,f.q,f.a); r.r=1u; }
    while (1) {
        /* Assertion, NOT an assumption or a forced successful exit. */
        require(r.n<CAP,1);
        v=0u; flags=0u;
        for (k=0u; k<6u; k++) {
            outcome=measure_generator(&r.e,f,rr,k,&r.s);
            v |= (outcome&1u)<<k;
            flags |= ((outcome>>1u)&1u)<<k;
        }
        r.history[r.n]=v|(flags<<6u); r.n++;
        if (after!=0u) {
            after--;
            if (after==0u) { r.branch=1u; break; }
        } else if (flags!=0u) {
            after=2u;
        } else {
            equal_count=(v==previous)?equal_count+1u:1u;
            previous=v;
            if (equal_count==3u) { r.branch=0u; break; }
        }
        rr++;
    }
    require(r.r+r.s<=1u,2);
    return r;
}
/* Decoder depends ONLY on observed history and branch, never actual E. */
Pauli correction(const Result *r) {
    Pauli c={0u,0u}; unsigned int i,j,col,v,match;
    if (r->branch==0u) {
        v=r->history[r->n-1u]&63u;
        for (j=0u; j<7u; j++) {
            col=((H[0]>>j)&1u) | (((H[1]>>j)&1u)<<1u)
                | (((H[2]>>j)&1u)<<2u);
            if ((v&7u)==col) c.x=1u<<j;
            if (((v>>3u)&7u)==col) c.z=1u<<j;
        }
#if FTEC_BROKEN_DECODER
        c.x=0u; c.z=0u;
#endif
        return c;
    }
    for (i=0u; i<FLAG_COUNT; i++) {
        if (FLAG_TABLE[i].n!=r->n) continue;
        match=1u;
        for (j=0u; j<r->n; j++) {
            if (FLAG_TABLE[i].history[j]!=r->history[j]) match=0u;
        }
        if (match) {
            c.x=FLAG_TABLE[i].x; c.z=FLAG_TABLE[i].z;
            return c;
        }
    }
    require(0,3); /* Missing reachable entry must fail, not prune a path. */
    return c;
}
int same_history(const Result *a, const Result *b) {
    unsigned int j;
    if (a->n!=b->n || a->branch!=b->branch) return 0;
    for (j=0u; j<a->n; j++)
        if (a->history[j]!=b->history[j]) return 0;
    return 1;
}
void check_residual(const Result *r) {
    Pauli c=correction(r);
    require(min_weight(multiply(c,r->e))<=r->s,4);
}
void check_pair(const Result *a, const Result *b) {
    Pauli delta;
    if (!same_history(a,b)) return;
    delta=multiply(a->e,b->e); /* E1^dagger E2, ignoring global phase */
    require(syndrome(delta)!=0u || in_stabilizer(delta),5);
}
#ifndef FTEC_NATIVE
Input choose_input(void) {
    Input f={0};
    f.mode=__VERIFIER_nondet_uint();
    if (f.mode==1u) {
        f.q=__VERIFIER_nondet_uint(); f.a=__VERIFIER_nondet_uint();
    } else if (f.mode==2u) {
        f.round=__VERIFIER_nondet_uint(); f.k=__VERIFIER_nondet_uint();
        f.op=__VERIFIER_nondet_uint(); f.p=__VERIFIER_nondet_uint();
    }
    return f;
}
int main(void) {
    Input f1=choose_input();
    Result a;
    if (!valid_input(f1)) return 0;
    a=run_model(f1);
#if FTEC_TASK != 2
    check_residual(&a);
#endif
#if FTEC_TASK != 1
    {
        Input f2=choose_input();
        Result b;
        if (!valid_input(f2)) return 0;
        b=run_model(f2);
#if FTEC_TASK == 0
        check_residual(&b);
#endif
        check_pair(&a,&b);
    }
#endif
    return 0;
}
#endif
