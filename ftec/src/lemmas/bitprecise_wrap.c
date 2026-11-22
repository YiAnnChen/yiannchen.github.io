/* Bit-precision sanity control: unsigned wraparound must be modelled exactly.
 * Expected TRUE (x==UINT_MAX implies x+1u==0u). Does not include scalar.c.
 */
extern unsigned int __VERIFIER_nondet_uint(void);
extern void __VERIFIER_error(void);
int main(void) {
 unsigned x=__VERIFIER_nondet_uint();
 if(x==4294967295u) { if(x+1u!=0u) { ERROR: __VERIFIER_error(); } }
 return 0;
}
