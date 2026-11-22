/* Bit-precision sanity control: x+1u<x is reachable (x==UINT_MAX) only under
 * bit-vector semantics. Expected FALSE. Does not include scalar.c.
 */
extern unsigned int __VERIFIER_nondet_uint(void);
extern void __VERIFIER_error(void);
int main(void) {
 unsigned x=__VERIFIER_nondet_uint();
 if(x+1u<x) { ERROR: __VERIFIER_error(); }
 return 0;
}
