/* Partition r1_k0_op9; task residual; t=1; v4_1. */
#include "scalar.c"
int main(void) {
unsigned p=__VERIFIER_nondet_uint();
 if(p<1u || p>1u) return 0;
 run(2,0,0,1u,0u,9u,p);
 check(er==0u && es==1u);
check(ec==correction(en,eb,eh0,eh1,eh2,eh3,eh4,eh5,eh6,eh7));
check(residual(ex^(ec&127u),ez^(ec>>7),es)); return 0; }
