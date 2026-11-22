#include "scalar.c"
int main(void) {
 unsigned x=__VERIFIER_nondet_uint()&127u,z=__VERIFIER_nondet_uint()&127u;
 unsigned r=__VERIFIER_nondet_uint(),s=__VERIFIER_nondet_uint();
 /* Check each bound before adding, avoiding unsigned wraparound. */
 if(r>1u || s>1u || r+s>1u) return 0;
 if(!residual(x,z,s)) return 0;
 check(residual(x,z,1u));
 return 0;
}
