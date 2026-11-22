/* Negative control for the new guard in residual(): s>1 is outside the
 * function's valid domain and must be reported as an error. Expected FALSE.
 */
#include "scalar.c"
int main(void) {
 unsigned x=__VERIFIER_nondet_uint()&127u,z=__VERIFIER_nondet_uint()&127u;
 residual(x,z,2u);
 return 0;
}
