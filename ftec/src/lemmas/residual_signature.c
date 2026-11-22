/* Unary consequence of residual<=1. No protocol execution. */
#include "scalar.c"
int main(void) {
 unsigned x=__VERIFIER_nondet_uint()&127u;
 unsigned z=__VERIFIER_nondet_uint()&127u;
 unsigned v=sy(x,z);
 if(!residual(x,z,1u)) return 0;
 check(parity(x)==((v&7u)!=0u));
 check(parity(z)==((v>>3)!=0u));
 return 0;
}
