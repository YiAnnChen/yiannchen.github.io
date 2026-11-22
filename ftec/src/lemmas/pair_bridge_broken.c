/* Negative control: omit the second execution's residual certificate.
 * A nontrivial logical Pauli in E2 is now permitted. Expected FALSE.
 */
#include "scalar.c"
int main(void) {
 unsigned ex1=__VERIFIER_nondet_uint()&127u;
 unsigned ez1=__VERIFIER_nondet_uint()&127u;
 unsigned ex2=__VERIFIER_nondet_uint()&127u;
 unsigned ez2=__VERIFIER_nondet_uint()&127u;
 unsigned cx=__VERIFIER_nondet_uint()&127u;
 unsigned cz=__VERIFIER_nondet_uint()&127u;
 if(!residual(ex1^cx,ez1^cz,1u)) return 0;
 check(sy(ex1^ex2,ez1^ez2)!=0u || member(ex1^ex2,ez1^ez2));
 return 0;
}
