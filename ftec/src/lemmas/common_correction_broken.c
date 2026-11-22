/* Negative control for common_correction: the second "correction" also reads
 * hidden state (es). After havocking es it can differ. Expected FALSE.
 */
#include "scalar.c"
int main(void) {
 unsigned n=__VERIFIER_nondet_uint(),b=__VERIFIER_nondet_uint()&1u;
 unsigned h0=__VERIFIER_nondet_uint()&4095u,h1=__VERIFIER_nondet_uint()&4095u;
 unsigned h2=__VERIFIER_nondet_uint()&4095u,h3=__VERIFIER_nondet_uint()&4095u;
 unsigned h4=__VERIFIER_nondet_uint()&4095u,h5=__VERIFIER_nondet_uint()&4095u;
 unsigned h6=__VERIFIER_nondet_uint()&4095u,h7=__VERIFIER_nondet_uint()&4095u;
 unsigned c1,c2;
 if(n<1u || n>8u) return 0;
 c1=correction(n,b,h0,h1,h2,h3,h4,h5,h6,h7);
 es=__VERIFIER_nondet_uint();
 c2=correction(n,b,h0,h1,h2,h3,h4,h5,h6,h7)^(es&1u);
 check(c1==c2);
 return 0;
}
