/* Machine check of "same complete observation -> same correction".
 * correction() is evaluated twice on the SAME observation arguments; between
 * the calls every global output variable is overwritten with arbitrary values.
 * TRUE means the result depends only on (n,b,h0..h7), not on hidden state.
 * Together with the per-partition check ec==correction(en,eb,eh0..eh7), this
 * links each run's applied correction to its observation alone.
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
 ex=__VERIFIER_nondet_uint(); ez=__VERIFIER_nondet_uint(); er=__VERIFIER_nondet_uint();
 es=__VERIFIER_nondet_uint(); en=__VERIFIER_nondet_uint(); eb=__VERIFIER_nondet_uint();
 ec=__VERIFIER_nondet_uint(); eh0=__VERIFIER_nondet_uint(); eh1=__VERIFIER_nondet_uint();
 eh2=__VERIFIER_nondet_uint(); eh3=__VERIFIER_nondet_uint(); eh4=__VERIFIER_nondet_uint();
 eh5=__VERIFIER_nondet_uint(); eh6=__VERIFIER_nondet_uint(); eh7=__VERIFIER_nondet_uint();
 c2=correction(n,b,h0,h1,h2,h3,h4,h5,h6,h7);
 check(c1==c2);
 return 0;
}
