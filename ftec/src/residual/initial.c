/* Partition initial; task residual; t=1; v4_1. */
#include "scalar.c"
int main(void) {
unsigned m=__VERIFIER_nondet_uint(),q=__VERIFIER_nondet_uint(),a=__VERIFIER_nondet_uint();
 if(m>1u || !valid(m,q,a,0,0,0,0)) return 0;
 run(m,q,a,0,0,0,0); check(es==0u && er<=1u);
check(ec==correction(en,eb,eh0,eh1,eh2,eh3,eh4,eh5,eh6,eh7));
check(residual(ex^(ec&127u),ez^(ec>>7),es)); return 0; }
