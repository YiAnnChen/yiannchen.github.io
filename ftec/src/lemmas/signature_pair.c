/* Binary consequence of the two unary signature certificates.
 * Common C is arbitrary; E1,E2 are PRE-correction errors.
 */
#include "scalar.c"
int main(void) {
 unsigned ex1=__VERIFIER_nondet_uint()&127u;
 unsigned ez1=__VERIFIER_nondet_uint()&127u;
 unsigned ex2=__VERIFIER_nondet_uint()&127u;
 unsigned ez2=__VERIFIER_nondet_uint()&127u;
 unsigned cx=__VERIFIER_nondet_uint()&127u;
 unsigned cz=__VERIFIER_nondet_uint()&127u;
 unsigned ax=ex1^cx,az=ez1^cz,bx=ex2^cx,bz=ez2^cz;
 unsigned va=sy(ax,az),vb=sy(bx,bz);
 if(parity(ax)!=((va&7u)!=0u) || parity(az)!=((va>>3)!=0u)) return 0;
 if(parity(bx)!=((vb&7u)!=0u) || parity(bz)!=((vb>>3)!=0u)) return 0;
 check((ax^bx)==(ex1^ex2) && (az^bz)==(ez1^ez2));
 check(sy(ex1^ex2,ez1^ez2)!=0u || member(ex1^ex2,ez1^ez2));
 return 0;
}
