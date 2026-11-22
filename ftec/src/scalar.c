/* Generated scalar Pauli-frame model. t=1; see README_zh.md. */
/* v4_1: edited from v2 scalar.c; every change is listed in CHANGES_zh.md. */
extern unsigned int __VERIFIER_nondet_uint(void);
extern void __VERIFIER_error(void) __attribute__((noreturn));
void check(int b) { if(!b) { ERROR: __VERIFIER_error(); } }
unsigned parity(unsigned v) { v^=v>>4; v^=v>>2; v^=v>>1; return v&1u; }
unsigned sy(unsigned x,unsigned z) {
 return parity(x&120u)|(parity(x&102u)<<1)|(parity(x&85u)<<2)
 |(parity(z&120u)<<3)|(parity(z&102u)<<4)|(parity(z&85u)<<5);
}
unsigned cx(unsigned x,unsigned a,unsigned b) { return x^(((x>>a)&1u)<<b); }
unsigned cz(unsigned z,unsigned a,unsigned b) { return z^(((z>>b)&1u)<<a); }
int member(unsigned x,unsigned z) { return sy(x,z)==0u && parity(x)==0u && parity(z)==0u; }
int residual(unsigned x,unsigned z,unsigned s) {
 check(s<=1u);
 if(member(x,z)) return 1;
 if(s==0u) return 0;
 if(member(x^1u,z^0u)) return 1;
 if(member(x^0u,z^1u)) return 1;
 if(member(x^1u,z^1u)) return 1;
 if(member(x^2u,z^0u)) return 1;
 if(member(x^0u,z^2u)) return 1;
 if(member(x^2u,z^2u)) return 1;
 if(member(x^4u,z^0u)) return 1;
 if(member(x^0u,z^4u)) return 1;
 if(member(x^4u,z^4u)) return 1;
 if(member(x^8u,z^0u)) return 1;
 if(member(x^0u,z^8u)) return 1;
 if(member(x^8u,z^8u)) return 1;
 if(member(x^16u,z^0u)) return 1;
 if(member(x^0u,z^16u)) return 1;
 if(member(x^16u,z^16u)) return 1;
 if(member(x^32u,z^0u)) return 1;
 if(member(x^0u,z^32u)) return 1;
 if(member(x^32u,z^32u)) return 1;
 if(member(x^64u,z^0u)) return 1;
 if(member(x^0u,z^64u)) return 1;
 if(member(x^64u,z^64u)) return 1;
 return 0;
}
unsigned decode(unsigned v) {
 unsigned x=0,z=0;
 if((v&7u)==4u) x=1u; if(((v>>3)&7u)==4u) z=1u;
 if((v&7u)==2u) x=2u; if(((v>>3)&7u)==2u) z=2u;
 if((v&7u)==6u) x=4u; if(((v>>3)&7u)==6u) z=4u;
 if((v&7u)==1u) x=8u; if(((v>>3)&7u)==1u) z=8u;
 if((v&7u)==5u) x=16u; if(((v>>3)&7u)==5u) z=16u;
 if((v&7u)==3u) x=32u; if(((v>>3)&7u)==3u) z=32u;
 if((v&7u)==7u) x=64u; if(((v>>3)&7u)==7u) z=64u;
return x|(z<<7); }
unsigned flaglookup(unsigned n,unsigned h0,unsigned h1,unsigned h2,unsigned h3,unsigned h4,unsigned h5,unsigned h6,unsigned h7) {
 if(n==3u && h0==64u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==65u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==72u && h1==8u && h2==8u) return 14336u;
 if(n==3u && h0==73u && h1==8u && h2==8u) return 14336u;
 if(n==3u && h0==96u && h1==32u && h2==32u) return 12288u;
 if(n==3u && h0==100u && h1==37u && h2==37u) return 12304u;
 if(n==3u && h0==76u && h1==13u && h2==13u) return 14352u;
 if(n==3u && h0==97u && h1==32u && h2==32u) return 12288u;
 if(n==3u && h0==101u && h1==37u && h2==37u) return 12304u;
 if(n==3u && h0==77u && h1==13u && h2==13u) return 14352u;
 if(n==3u && h0==120u && h1==56u && h2==56u) return 8192u;
 if(n==3u && h0==122u && h1==59u && h2==59u) return 8224u;
 if(n==3u && h0==98u && h1==35u && h2==35u) return 12320u;
 if(n==3u && h0==121u && h1==56u && h2==56u) return 8192u;
 if(n==3u && h0==123u && h1==59u && h2==59u) return 8224u;
 if(n==3u && h0==99u && h1==35u && h2==35u) return 12320u;
 if(n==3u && h0==128u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==130u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==144u && h1==16u && h2==16u) return 12800u;
 if(n==3u && h0==146u && h1==16u && h2==16u) return 12800u;
 if(n==3u && h0==160u && h1==32u && h2==32u) return 12288u;
 if(n==3u && h0==164u && h1==38u && h2==38u) return 12292u;
 if(n==3u && h0==148u && h1==22u && h2==22u) return 12804u;
 if(n==3u && h0==162u && h1==32u && h2==32u) return 12288u;
 if(n==3u && h0==166u && h1==38u && h2==38u) return 12292u;
 if(n==3u && h0==150u && h1==22u && h2==22u) return 12804u;
 if(n==3u && h0==184u && h1==56u && h2==56u) return 8192u;
 if(n==3u && h0==184u && h1==59u && h2==59u) return 8224u;
 if(n==3u && h0==160u && h1==35u && h2==35u) return 12320u;
 if(n==3u && h0==186u && h1==56u && h2==56u) return 8192u;
 if(n==3u && h0==186u && h1==59u && h2==59u) return 8224u;
 if(n==3u && h0==162u && h1==35u && h2==35u) return 12320u;
 if(n==3u && h0==256u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==260u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==288u && h1==32u && h2==32u) return 10752u;
 if(n==3u && h0==292u && h1==32u && h2==32u) return 10752u;
 if(n==3u && h0==272u && h1==16u && h2==16u) return 10240u;
 if(n==3u && h0==272u && h1==22u && h2==22u) return 10244u;
 if(n==3u && h0==288u && h1==38u && h2==38u) return 10756u;
 if(n==3u && h0==276u && h1==16u && h2==16u) return 10240u;
 if(n==3u && h0==276u && h1==22u && h2==22u) return 10244u;
 if(n==3u && h0==292u && h1==38u && h2==38u) return 10756u;
 if(n==3u && h0==312u && h1==56u && h2==56u) return 8192u;
 if(n==3u && h0==312u && h1==61u && h2==61u) return 8208u;
 if(n==3u && h0==272u && h1==21u && h2==21u) return 10256u;
 if(n==3u && h0==316u && h1==56u && h2==56u) return 8192u;
 if(n==3u && h0==316u && h1==61u && h2==61u) return 8208u;
 if(n==3u && h0==276u && h1==21u && h2==21u) return 10256u;
 if(n==3u && h0==512u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==512u && h1==1u && h2==1u) return 112u;
 if(n==3u && h0==520u && h1==1u && h2==1u) return 112u;
 if(n==3u && h0==520u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==512u && h1==4u && h2==4u) return 96u;
 if(n==3u && h0==520u && h1==4u && h2==4u) return 96u;
 if(n==3u && h0==544u && h1==44u && h2==44u) return 2144u;
 if(n==3u && h0==552u && h1==44u && h2==44u) return 2144u;
 if(n==3u && h0==544u && h1==41u && h2==41u) return 2160u;
 if(n==3u && h0==552u && h1==41u && h2==41u) return 2160u;
 if(n==3u && h0==512u && h1==7u && h2==7u) return 64u;
 if(n==3u && h0==520u && h1==7u && h2==7u) return 64u;
 if(n==3u && h0==528u && h1==31u && h2==31u) return 4160u;
 if(n==3u && h0==536u && h1==31u && h2==31u) return 4160u;
 if(n==3u && h0==528u && h1==28u && h2==28u) return 4192u;
 if(n==3u && h0==536u && h1==28u && h2==28u) return 4192u;
 if(n==3u && h0==1024u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==1024u && h1==2u && h2==2u) return 100u;
 if(n==3u && h0==1040u && h1==2u && h2==2u) return 100u;
 if(n==3u && h0==1040u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==1024u && h1==4u && h2==4u) return 96u;
 if(n==3u && h0==1040u && h1==4u && h2==4u) return 96u;
 if(n==3u && h0==1056u && h1==52u && h2==52u) return 608u;
 if(n==3u && h0==1072u && h1==52u && h2==52u) return 608u;
 if(n==3u && h0==1056u && h1==50u && h2==50u) return 612u;
 if(n==3u && h0==1072u && h1==50u && h2==50u) return 612u;
 if(n==3u && h0==1024u && h1==7u && h2==7u) return 64u;
 if(n==3u && h0==1040u && h1==7u && h2==7u) return 64u;
 if(n==3u && h0==1024u && h1==31u && h2==31u) return 4160u;
 if(n==3u && h0==1040u && h1==31u && h2==31u) return 4160u;
 if(n==3u && h0==1024u && h1==28u && h2==28u) return 4192u;
 if(n==3u && h0==1040u && h1==28u && h2==28u) return 4192u;
 if(n==3u && h0==2048u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==2048u && h1==4u && h2==4u) return 84u;
 if(n==3u && h0==2080u && h1==4u && h2==4u) return 84u;
 if(n==3u && h0==2080u && h1==0u && h2==0u) return 0u;
 if(n==3u && h0==2048u && h1==2u && h2==2u) return 80u;
 if(n==3u && h0==2080u && h1==2u && h2==2u) return 80u;
 if(n==3u && h0==2048u && h1==50u && h2==50u) return 592u;
 if(n==3u && h0==2080u && h1==50u && h2==50u) return 592u;
 if(n==3u && h0==2048u && h1==52u && h2==52u) return 596u;
 if(n==3u && h0==2080u && h1==52u && h2==52u) return 596u;
 if(n==3u && h0==2048u && h1==7u && h2==7u) return 64u;
 if(n==3u && h0==2080u && h1==7u && h2==7u) return 64u;
 if(n==3u && h0==2048u && h1==47u && h2==47u) return 2112u;
 if(n==3u && h0==2080u && h1==47u && h2==47u) return 2112u;
 if(n==3u && h0==2048u && h1==42u && h2==42u) return 2128u;
 if(n==3u && h0==2080u && h1==42u && h2==42u) return 2128u;
 if(n==4u && h0==0u && h1==64u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==65u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==72u && h2==8u && h3==8u) return 14336u;
 if(n==4u && h0==0u && h1==73u && h2==8u && h3==8u) return 14336u;
 if(n==4u && h0==0u && h1==96u && h2==32u && h3==32u) return 12288u;
 if(n==4u && h0==0u && h1==100u && h2==37u && h3==37u) return 12304u;
 if(n==4u && h0==0u && h1==76u && h2==13u && h3==13u) return 14352u;
 if(n==4u && h0==0u && h1==97u && h2==32u && h3==32u) return 12288u;
 if(n==4u && h0==0u && h1==101u && h2==37u && h3==37u) return 12304u;
 if(n==4u && h0==0u && h1==77u && h2==13u && h3==13u) return 14352u;
 if(n==4u && h0==0u && h1==120u && h2==56u && h3==56u) return 8192u;
 if(n==4u && h0==0u && h1==122u && h2==59u && h3==59u) return 8224u;
 if(n==4u && h0==0u && h1==98u && h2==35u && h3==35u) return 12320u;
 if(n==4u && h0==0u && h1==121u && h2==56u && h3==56u) return 8192u;
 if(n==4u && h0==0u && h1==123u && h2==59u && h3==59u) return 8224u;
 if(n==4u && h0==0u && h1==99u && h2==35u && h3==35u) return 12320u;
 if(n==4u && h0==0u && h1==128u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==130u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==144u && h2==16u && h3==16u) return 12800u;
 if(n==4u && h0==0u && h1==146u && h2==16u && h3==16u) return 12800u;
 if(n==4u && h0==0u && h1==160u && h2==32u && h3==32u) return 12288u;
 if(n==4u && h0==0u && h1==164u && h2==38u && h3==38u) return 12292u;
 if(n==4u && h0==0u && h1==148u && h2==22u && h3==22u) return 12804u;
 if(n==4u && h0==0u && h1==162u && h2==32u && h3==32u) return 12288u;
 if(n==4u && h0==0u && h1==166u && h2==38u && h3==38u) return 12292u;
 if(n==4u && h0==0u && h1==150u && h2==22u && h3==22u) return 12804u;
 if(n==4u && h0==0u && h1==184u && h2==56u && h3==56u) return 8192u;
 if(n==4u && h0==0u && h1==184u && h2==59u && h3==59u) return 8224u;
 if(n==4u && h0==0u && h1==160u && h2==35u && h3==35u) return 12320u;
 if(n==4u && h0==0u && h1==186u && h2==56u && h3==56u) return 8192u;
 if(n==4u && h0==0u && h1==186u && h2==59u && h3==59u) return 8224u;
 if(n==4u && h0==0u && h1==162u && h2==35u && h3==35u) return 12320u;
 if(n==4u && h0==0u && h1==256u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==260u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==288u && h2==32u && h3==32u) return 10752u;
 if(n==4u && h0==0u && h1==292u && h2==32u && h3==32u) return 10752u;
 if(n==4u && h0==0u && h1==272u && h2==16u && h3==16u) return 10240u;
 if(n==4u && h0==0u && h1==272u && h2==22u && h3==22u) return 10244u;
 if(n==4u && h0==0u && h1==288u && h2==38u && h3==38u) return 10756u;
 if(n==4u && h0==0u && h1==276u && h2==16u && h3==16u) return 10240u;
 if(n==4u && h0==0u && h1==276u && h2==22u && h3==22u) return 10244u;
 if(n==4u && h0==0u && h1==292u && h2==38u && h3==38u) return 10756u;
 if(n==4u && h0==0u && h1==312u && h2==56u && h3==56u) return 8192u;
 if(n==4u && h0==0u && h1==312u && h2==61u && h3==61u) return 8208u;
 if(n==4u && h0==0u && h1==272u && h2==21u && h3==21u) return 10256u;
 if(n==4u && h0==0u && h1==316u && h2==56u && h3==56u) return 8192u;
 if(n==4u && h0==0u && h1==316u && h2==61u && h3==61u) return 8208u;
 if(n==4u && h0==0u && h1==276u && h2==21u && h3==21u) return 10256u;
 if(n==4u && h0==0u && h1==512u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==512u && h2==1u && h3==1u) return 112u;
 if(n==4u && h0==0u && h1==520u && h2==1u && h3==1u) return 112u;
 if(n==4u && h0==0u && h1==520u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==512u && h2==4u && h3==4u) return 96u;
 if(n==4u && h0==0u && h1==520u && h2==4u && h3==4u) return 96u;
 if(n==4u && h0==0u && h1==544u && h2==44u && h3==44u) return 2144u;
 if(n==4u && h0==0u && h1==552u && h2==44u && h3==44u) return 2144u;
 if(n==4u && h0==0u && h1==544u && h2==41u && h3==41u) return 2160u;
 if(n==4u && h0==0u && h1==552u && h2==41u && h3==41u) return 2160u;
 if(n==4u && h0==0u && h1==512u && h2==7u && h3==7u) return 64u;
 if(n==4u && h0==0u && h1==520u && h2==7u && h3==7u) return 64u;
 if(n==4u && h0==0u && h1==528u && h2==31u && h3==31u) return 4160u;
 if(n==4u && h0==0u && h1==536u && h2==31u && h3==31u) return 4160u;
 if(n==4u && h0==0u && h1==528u && h2==28u && h3==28u) return 4192u;
 if(n==4u && h0==0u && h1==536u && h2==28u && h3==28u) return 4192u;
 if(n==4u && h0==0u && h1==1024u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==1024u && h2==2u && h3==2u) return 100u;
 if(n==4u && h0==0u && h1==1040u && h2==2u && h3==2u) return 100u;
 if(n==4u && h0==0u && h1==1040u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==1024u && h2==4u && h3==4u) return 96u;
 if(n==4u && h0==0u && h1==1040u && h2==4u && h3==4u) return 96u;
 if(n==4u && h0==0u && h1==1056u && h2==52u && h3==52u) return 608u;
 if(n==4u && h0==0u && h1==1072u && h2==52u && h3==52u) return 608u;
 if(n==4u && h0==0u && h1==1056u && h2==50u && h3==50u) return 612u;
 if(n==4u && h0==0u && h1==1072u && h2==50u && h3==50u) return 612u;
 if(n==4u && h0==0u && h1==1024u && h2==7u && h3==7u) return 64u;
 if(n==4u && h0==0u && h1==1040u && h2==7u && h3==7u) return 64u;
 if(n==4u && h0==0u && h1==1024u && h2==31u && h3==31u) return 4160u;
 if(n==4u && h0==0u && h1==1040u && h2==31u && h3==31u) return 4160u;
 if(n==4u && h0==0u && h1==1024u && h2==28u && h3==28u) return 4192u;
 if(n==4u && h0==0u && h1==1040u && h2==28u && h3==28u) return 4192u;
 if(n==4u && h0==0u && h1==2048u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==2048u && h2==4u && h3==4u) return 84u;
 if(n==4u && h0==0u && h1==2080u && h2==4u && h3==4u) return 84u;
 if(n==4u && h0==0u && h1==2080u && h2==0u && h3==0u) return 0u;
 if(n==4u && h0==0u && h1==2048u && h2==2u && h3==2u) return 80u;
 if(n==4u && h0==0u && h1==2080u && h2==2u && h3==2u) return 80u;
 if(n==4u && h0==0u && h1==2048u && h2==50u && h3==50u) return 592u;
 if(n==4u && h0==0u && h1==2080u && h2==50u && h3==50u) return 592u;
 if(n==4u && h0==0u && h1==2048u && h2==52u && h3==52u) return 596u;
 if(n==4u && h0==0u && h1==2080u && h2==52u && h3==52u) return 596u;
 if(n==4u && h0==0u && h1==2048u && h2==7u && h3==7u) return 64u;
 if(n==4u && h0==0u && h1==2080u && h2==7u && h3==7u) return 64u;
 if(n==4u && h0==0u && h1==2048u && h2==47u && h3==47u) return 2112u;
 if(n==4u && h0==0u && h1==2080u && h2==47u && h3==47u) return 2112u;
 if(n==4u && h0==0u && h1==2048u && h2==42u && h3==42u) return 2128u;
 if(n==4u && h0==0u && h1==2080u && h2==42u && h3==42u) return 2128u;
 if(n==5u && h0==0u && h1==0u && h2==64u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==65u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==72u && h3==8u && h4==8u) return 14336u;
 if(n==5u && h0==0u && h1==0u && h2==73u && h3==8u && h4==8u) return 14336u;
 if(n==5u && h0==0u && h1==0u && h2==96u && h3==32u && h4==32u) return 12288u;
 if(n==5u && h0==0u && h1==0u && h2==100u && h3==37u && h4==37u) return 12304u;
 if(n==5u && h0==0u && h1==0u && h2==76u && h3==13u && h4==13u) return 14352u;
 if(n==5u && h0==0u && h1==0u && h2==97u && h3==32u && h4==32u) return 12288u;
 if(n==5u && h0==0u && h1==0u && h2==101u && h3==37u && h4==37u) return 12304u;
 if(n==5u && h0==0u && h1==0u && h2==77u && h3==13u && h4==13u) return 14352u;
 if(n==5u && h0==0u && h1==0u && h2==120u && h3==56u && h4==56u) return 8192u;
 if(n==5u && h0==0u && h1==0u && h2==122u && h3==59u && h4==59u) return 8224u;
 if(n==5u && h0==0u && h1==0u && h2==98u && h3==35u && h4==35u) return 12320u;
 if(n==5u && h0==0u && h1==0u && h2==121u && h3==56u && h4==56u) return 8192u;
 if(n==5u && h0==0u && h1==0u && h2==123u && h3==59u && h4==59u) return 8224u;
 if(n==5u && h0==0u && h1==0u && h2==99u && h3==35u && h4==35u) return 12320u;
 if(n==5u && h0==0u && h1==0u && h2==128u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==130u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==144u && h3==16u && h4==16u) return 12800u;
 if(n==5u && h0==0u && h1==0u && h2==146u && h3==16u && h4==16u) return 12800u;
 if(n==5u && h0==0u && h1==0u && h2==160u && h3==32u && h4==32u) return 12288u;
 if(n==5u && h0==0u && h1==0u && h2==164u && h3==38u && h4==38u) return 12292u;
 if(n==5u && h0==0u && h1==0u && h2==148u && h3==22u && h4==22u) return 12804u;
 if(n==5u && h0==0u && h1==0u && h2==162u && h3==32u && h4==32u) return 12288u;
 if(n==5u && h0==0u && h1==0u && h2==166u && h3==38u && h4==38u) return 12292u;
 if(n==5u && h0==0u && h1==0u && h2==150u && h3==22u && h4==22u) return 12804u;
 if(n==5u && h0==0u && h1==0u && h2==184u && h3==56u && h4==56u) return 8192u;
 if(n==5u && h0==0u && h1==0u && h2==184u && h3==59u && h4==59u) return 8224u;
 if(n==5u && h0==0u && h1==0u && h2==160u && h3==35u && h4==35u) return 12320u;
 if(n==5u && h0==0u && h1==0u && h2==186u && h3==56u && h4==56u) return 8192u;
 if(n==5u && h0==0u && h1==0u && h2==186u && h3==59u && h4==59u) return 8224u;
 if(n==5u && h0==0u && h1==0u && h2==162u && h3==35u && h4==35u) return 12320u;
 if(n==5u && h0==0u && h1==0u && h2==256u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==260u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==288u && h3==32u && h4==32u) return 10752u;
 if(n==5u && h0==0u && h1==0u && h2==292u && h3==32u && h4==32u) return 10752u;
 if(n==5u && h0==0u && h1==0u && h2==272u && h3==16u && h4==16u) return 10240u;
 if(n==5u && h0==0u && h1==0u && h2==272u && h3==22u && h4==22u) return 10244u;
 if(n==5u && h0==0u && h1==0u && h2==288u && h3==38u && h4==38u) return 10756u;
 if(n==5u && h0==0u && h1==0u && h2==276u && h3==16u && h4==16u) return 10240u;
 if(n==5u && h0==0u && h1==0u && h2==276u && h3==22u && h4==22u) return 10244u;
 if(n==5u && h0==0u && h1==0u && h2==292u && h3==38u && h4==38u) return 10756u;
 if(n==5u && h0==0u && h1==0u && h2==312u && h3==56u && h4==56u) return 8192u;
 if(n==5u && h0==0u && h1==0u && h2==312u && h3==61u && h4==61u) return 8208u;
 if(n==5u && h0==0u && h1==0u && h2==272u && h3==21u && h4==21u) return 10256u;
 if(n==5u && h0==0u && h1==0u && h2==316u && h3==56u && h4==56u) return 8192u;
 if(n==5u && h0==0u && h1==0u && h2==316u && h3==61u && h4==61u) return 8208u;
 if(n==5u && h0==0u && h1==0u && h2==276u && h3==21u && h4==21u) return 10256u;
 if(n==5u && h0==0u && h1==0u && h2==512u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==512u && h3==1u && h4==1u) return 112u;
 if(n==5u && h0==0u && h1==0u && h2==520u && h3==1u && h4==1u) return 112u;
 if(n==5u && h0==0u && h1==0u && h2==520u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==512u && h3==4u && h4==4u) return 96u;
 if(n==5u && h0==0u && h1==0u && h2==520u && h3==4u && h4==4u) return 96u;
 if(n==5u && h0==0u && h1==0u && h2==544u && h3==44u && h4==44u) return 2144u;
 if(n==5u && h0==0u && h1==0u && h2==552u && h3==44u && h4==44u) return 2144u;
 if(n==5u && h0==0u && h1==0u && h2==544u && h3==41u && h4==41u) return 2160u;
 if(n==5u && h0==0u && h1==0u && h2==552u && h3==41u && h4==41u) return 2160u;
 if(n==5u && h0==0u && h1==0u && h2==512u && h3==7u && h4==7u) return 64u;
 if(n==5u && h0==0u && h1==0u && h2==520u && h3==7u && h4==7u) return 64u;
 if(n==5u && h0==0u && h1==0u && h2==528u && h3==31u && h4==31u) return 4160u;
 if(n==5u && h0==0u && h1==0u && h2==536u && h3==31u && h4==31u) return 4160u;
 if(n==5u && h0==0u && h1==0u && h2==528u && h3==28u && h4==28u) return 4192u;
 if(n==5u && h0==0u && h1==0u && h2==536u && h3==28u && h4==28u) return 4192u;
 if(n==5u && h0==0u && h1==0u && h2==1024u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==1024u && h3==2u && h4==2u) return 100u;
 if(n==5u && h0==0u && h1==0u && h2==1040u && h3==2u && h4==2u) return 100u;
 if(n==5u && h0==0u && h1==0u && h2==1040u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==1024u && h3==4u && h4==4u) return 96u;
 if(n==5u && h0==0u && h1==0u && h2==1040u && h3==4u && h4==4u) return 96u;
 if(n==5u && h0==0u && h1==0u && h2==1056u && h3==52u && h4==52u) return 608u;
 if(n==5u && h0==0u && h1==0u && h2==1072u && h3==52u && h4==52u) return 608u;
 if(n==5u && h0==0u && h1==0u && h2==1056u && h3==50u && h4==50u) return 612u;
 if(n==5u && h0==0u && h1==0u && h2==1072u && h3==50u && h4==50u) return 612u;
 if(n==5u && h0==0u && h1==0u && h2==1024u && h3==7u && h4==7u) return 64u;
 if(n==5u && h0==0u && h1==0u && h2==1040u && h3==7u && h4==7u) return 64u;
 if(n==5u && h0==0u && h1==0u && h2==1024u && h3==31u && h4==31u) return 4160u;
 if(n==5u && h0==0u && h1==0u && h2==1040u && h3==31u && h4==31u) return 4160u;
 if(n==5u && h0==0u && h1==0u && h2==1024u && h3==28u && h4==28u) return 4192u;
 if(n==5u && h0==0u && h1==0u && h2==1040u && h3==28u && h4==28u) return 4192u;
 if(n==5u && h0==0u && h1==0u && h2==2048u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==2048u && h3==4u && h4==4u) return 84u;
 if(n==5u && h0==0u && h1==0u && h2==2080u && h3==4u && h4==4u) return 84u;
 if(n==5u && h0==0u && h1==0u && h2==2080u && h3==0u && h4==0u) return 0u;
 if(n==5u && h0==0u && h1==0u && h2==2048u && h3==2u && h4==2u) return 80u;
 if(n==5u && h0==0u && h1==0u && h2==2080u && h3==2u && h4==2u) return 80u;
 if(n==5u && h0==0u && h1==0u && h2==2048u && h3==50u && h4==50u) return 592u;
 if(n==5u && h0==0u && h1==0u && h2==2080u && h3==50u && h4==50u) return 592u;
 if(n==5u && h0==0u && h1==0u && h2==2048u && h3==52u && h4==52u) return 596u;
 if(n==5u && h0==0u && h1==0u && h2==2080u && h3==52u && h4==52u) return 596u;
 if(n==5u && h0==0u && h1==0u && h2==2048u && h3==7u && h4==7u) return 64u;
 if(n==5u && h0==0u && h1==0u && h2==2080u && h3==7u && h4==7u) return 64u;
 if(n==5u && h0==0u && h1==0u && h2==2048u && h3==47u && h4==47u) return 2112u;
 if(n==5u && h0==0u && h1==0u && h2==2080u && h3==47u && h4==47u) return 2112u;
 if(n==5u && h0==0u && h1==0u && h2==2048u && h3==42u && h4==42u) return 2128u;
 if(n==5u && h0==0u && h1==0u && h2==2080u && h3==42u && h4==42u) return 2128u;
 return 0x80000000u; }
unsigned correction(unsigned n,unsigned b,unsigned h0,unsigned h1,unsigned h2,unsigned h3,unsigned h4,unsigned h5,unsigned h6,unsigned h7) {
 unsigned last;
 if(b) return flaglookup(n,h0,h1,h2,h3,h4,h5,h6,h7);
 last=n==1u?h0:n==2u?h1:n==3u?h2:n==4u?h3:n==5u?h4:n==6u?h5:n==7u?h6:h7;
 return decode(last&63u); }
unsigned measure(unsigned x,unsigned z,unsigned rr,unsigned k,unsigned mode,unsigned fr,unsigned fk,unsigned fo,unsigned fp) {
 unsigned o=0; x&=127u; z&=127u;
 if(k==0u) {
 if(mode==2u && rr==fr && fk==0u && fo==0u) x^=128u;
 if(mode==2u && rr==fr && fk==0u && fo==1u) z^=256u;
 x=cx(x,3u,7u); z=cz(z,3u,7u);
 if(mode==2u && rr==fr && fk==0u && fo==2u) { x^=((fp&1u)<<3)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<3)|(((fp>>3)&1u)<<7); }
 x=cx(x,8u,7u); z=cz(z,8u,7u);
 if(mode==2u && rr==fr && fk==0u && fo==3u) { x^=((fp&1u)<<8)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<8)|(((fp>>3)&1u)<<7); }
 x=cx(x,4u,7u); z=cz(z,4u,7u);
 if(mode==2u && rr==fr && fk==0u && fo==4u) { x^=((fp&1u)<<4)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<4)|(((fp>>3)&1u)<<7); }
 x=cx(x,5u,7u); z=cz(z,5u,7u);
 if(mode==2u && rr==fr && fk==0u && fo==5u) { x^=((fp&1u)<<5)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<5)|(((fp>>3)&1u)<<7); }
 x=cx(x,8u,7u); z=cz(z,8u,7u);
 if(mode==2u && rr==fr && fk==0u && fo==6u) { x^=((fp&1u)<<8)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<8)|(((fp>>3)&1u)<<7); }
 x=cx(x,6u,7u); z=cz(z,6u,7u);
 if(mode==2u && rr==fr && fk==0u && fo==7u) { x^=((fp&1u)<<6)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<6)|(((fp>>3)&1u)<<7); }
 if(mode==2u && rr==fr && fk==0u && fo==8u) x^=128u;
 o|=(((x>>7)&1u)<<0);
 if(mode==2u && rr==fr && fk==0u && fo==9u) z^=256u;
 o|=(((z>>8)&1u)<<1);
 }
 if(k==1u) {
 if(mode==2u && rr==fr && fk==1u && fo==0u) x^=128u;
 if(mode==2u && rr==fr && fk==1u && fo==1u) z^=256u;
 x=cx(x,1u,7u); z=cz(z,1u,7u);
 if(mode==2u && rr==fr && fk==1u && fo==2u) { x^=((fp&1u)<<1)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<1)|(((fp>>3)&1u)<<7); }
 x=cx(x,8u,7u); z=cz(z,8u,7u);
 if(mode==2u && rr==fr && fk==1u && fo==3u) { x^=((fp&1u)<<8)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<8)|(((fp>>3)&1u)<<7); }
 x=cx(x,2u,7u); z=cz(z,2u,7u);
 if(mode==2u && rr==fr && fk==1u && fo==4u) { x^=((fp&1u)<<2)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<2)|(((fp>>3)&1u)<<7); }
 x=cx(x,5u,7u); z=cz(z,5u,7u);
 if(mode==2u && rr==fr && fk==1u && fo==5u) { x^=((fp&1u)<<5)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<5)|(((fp>>3)&1u)<<7); }
 x=cx(x,8u,7u); z=cz(z,8u,7u);
 if(mode==2u && rr==fr && fk==1u && fo==6u) { x^=((fp&1u)<<8)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<8)|(((fp>>3)&1u)<<7); }
 x=cx(x,6u,7u); z=cz(z,6u,7u);
 if(mode==2u && rr==fr && fk==1u && fo==7u) { x^=((fp&1u)<<6)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<6)|(((fp>>3)&1u)<<7); }
 if(mode==2u && rr==fr && fk==1u && fo==8u) x^=128u;
 o|=(((x>>7)&1u)<<0);
 if(mode==2u && rr==fr && fk==1u && fo==9u) z^=256u;
 o|=(((z>>8)&1u)<<1);
 }
 if(k==2u) {
 if(mode==2u && rr==fr && fk==2u && fo==0u) x^=128u;
 if(mode==2u && rr==fr && fk==2u && fo==1u) z^=256u;
 x=cx(x,0u,7u); z=cz(z,0u,7u);
 if(mode==2u && rr==fr && fk==2u && fo==2u) { x^=((fp&1u)<<0)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<0)|(((fp>>3)&1u)<<7); }
 x=cx(x,8u,7u); z=cz(z,8u,7u);
 if(mode==2u && rr==fr && fk==2u && fo==3u) { x^=((fp&1u)<<8)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<8)|(((fp>>3)&1u)<<7); }
 x=cx(x,2u,7u); z=cz(z,2u,7u);
 if(mode==2u && rr==fr && fk==2u && fo==4u) { x^=((fp&1u)<<2)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<2)|(((fp>>3)&1u)<<7); }
 x=cx(x,4u,7u); z=cz(z,4u,7u);
 if(mode==2u && rr==fr && fk==2u && fo==5u) { x^=((fp&1u)<<4)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<4)|(((fp>>3)&1u)<<7); }
 x=cx(x,8u,7u); z=cz(z,8u,7u);
 if(mode==2u && rr==fr && fk==2u && fo==6u) { x^=((fp&1u)<<8)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<8)|(((fp>>3)&1u)<<7); }
 x=cx(x,6u,7u); z=cz(z,6u,7u);
 if(mode==2u && rr==fr && fk==2u && fo==7u) { x^=((fp&1u)<<6)|(((fp>>2)&1u)<<7); z^=(((fp>>1)&1u)<<6)|(((fp>>3)&1u)<<7); }
 if(mode==2u && rr==fr && fk==2u && fo==8u) x^=128u;
 o|=(((x>>7)&1u)<<0);
 if(mode==2u && rr==fr && fk==2u && fo==9u) z^=256u;
 o|=(((z>>8)&1u)<<1);
 }
 if(k==3u) {
 if(mode==2u && rr==fr && fk==3u && fo==0u) z^=128u;
 if(mode==2u && rr==fr && fk==3u && fo==1u) x^=256u;
 x=cx(x,7u,3u); z=cz(z,7u,3u);
 if(mode==2u && rr==fr && fk==3u && fo==2u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<3); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<3); }
 x=cx(x,7u,8u); z=cz(z,7u,8u);
 if(mode==2u && rr==fr && fk==3u && fo==3u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<8); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<8); }
 x=cx(x,7u,4u); z=cz(z,7u,4u);
 if(mode==2u && rr==fr && fk==3u && fo==4u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<4); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<4); }
 x=cx(x,7u,5u); z=cz(z,7u,5u);
 if(mode==2u && rr==fr && fk==3u && fo==5u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<5); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<5); }
 x=cx(x,7u,8u); z=cz(z,7u,8u);
 if(mode==2u && rr==fr && fk==3u && fo==6u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<8); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<8); }
 x=cx(x,7u,6u); z=cz(z,7u,6u);
 if(mode==2u && rr==fr && fk==3u && fo==7u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<6); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<6); }
 if(mode==2u && rr==fr && fk==3u && fo==8u) z^=128u;
 o|=(((z>>7)&1u)<<0);
 if(mode==2u && rr==fr && fk==3u && fo==9u) x^=256u;
 o|=(((x>>8)&1u)<<1);
 }
 if(k==4u) {
 if(mode==2u && rr==fr && fk==4u && fo==0u) z^=128u;
 if(mode==2u && rr==fr && fk==4u && fo==1u) x^=256u;
 x=cx(x,7u,1u); z=cz(z,7u,1u);
 if(mode==2u && rr==fr && fk==4u && fo==2u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<1); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<1); }
 x=cx(x,7u,8u); z=cz(z,7u,8u);
 if(mode==2u && rr==fr && fk==4u && fo==3u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<8); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<8); }
 x=cx(x,7u,2u); z=cz(z,7u,2u);
 if(mode==2u && rr==fr && fk==4u && fo==4u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<2); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<2); }
 x=cx(x,7u,5u); z=cz(z,7u,5u);
 if(mode==2u && rr==fr && fk==4u && fo==5u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<5); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<5); }
 x=cx(x,7u,8u); z=cz(z,7u,8u);
 if(mode==2u && rr==fr && fk==4u && fo==6u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<8); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<8); }
 x=cx(x,7u,6u); z=cz(z,7u,6u);
 if(mode==2u && rr==fr && fk==4u && fo==7u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<6); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<6); }
 if(mode==2u && rr==fr && fk==4u && fo==8u) z^=128u;
 o|=(((z>>7)&1u)<<0);
 if(mode==2u && rr==fr && fk==4u && fo==9u) x^=256u;
 o|=(((x>>8)&1u)<<1);
 }
 if(k==5u) {
 if(mode==2u && rr==fr && fk==5u && fo==0u) z^=128u;
 if(mode==2u && rr==fr && fk==5u && fo==1u) x^=256u;
 x=cx(x,7u,0u); z=cz(z,7u,0u);
 if(mode==2u && rr==fr && fk==5u && fo==2u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<0); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<0); }
 x=cx(x,7u,8u); z=cz(z,7u,8u);
 if(mode==2u && rr==fr && fk==5u && fo==3u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<8); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<8); }
 x=cx(x,7u,2u); z=cz(z,7u,2u);
 if(mode==2u && rr==fr && fk==5u && fo==4u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<2); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<2); }
 x=cx(x,7u,4u); z=cz(z,7u,4u);
 if(mode==2u && rr==fr && fk==5u && fo==5u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<4); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<4); }
 x=cx(x,7u,8u); z=cz(z,7u,8u);
 if(mode==2u && rr==fr && fk==5u && fo==6u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<8); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<8); }
 x=cx(x,7u,6u); z=cz(z,7u,6u);
 if(mode==2u && rr==fr && fk==5u && fo==7u) { x^=((fp&1u)<<7)|(((fp>>2)&1u)<<6); z^=(((fp>>1)&1u)<<7)|(((fp>>3)&1u)<<6); }
 if(mode==2u && rr==fr && fk==5u && fo==8u) z^=128u;
 o|=(((z>>7)&1u)<<0);
 if(mode==2u && rr==fr && fk==5u && fo==9u) x^=256u;
 o|=(((x>>8)&1u)<<1);
 }
return (x&127u)|((z&127u)<<7)|(o<<14); }
unsigned ex,ez,er,es,en,eb,ec,eh0,eh1,eh2,eh3,eh4,eh5,eh6,eh7;
void run(unsigned mode,unsigned q,unsigned a,unsigned fr,unsigned fk,unsigned fo,unsigned fp) {
 unsigned x=0,z=0,r=0,s=0,n=0,branch=0,prev=64,count=0,after=0,rr=1;
 unsigned h0=0,h1=0,h2=0,h3=0,h4=0,h5=0,h6=0,h7=0,v,flags,k,w,word,cor;
 if(mode==1u) { x=(a&1u)<<q; z=((a>>1)&1u)<<q; r=1; }
 while(1) {
  check(n<8u); v=0; flags=0;
  for(k=0;k<6u;k++) {
   w=measure(x,z,rr,k,mode,fr,fk,fo,fp); x=w&127u; z=(w>>7)&127u;
   v|=((w>>14)&1u)<<k; flags|=((w>>15)&1u)<<k;
   if(mode==2u && rr==fr && k==fk) s++;
  }
  word=v|(flags<<6);
 if(n==0u) h0=word;
 if(n==1u) h1=word;
 if(n==2u) h2=word;
 if(n==3u) h3=word;
 if(n==4u) h4=word;
 if(n==5u) h5=word;
 if(n==6u) h6=word;
 if(n==7u) h7=word;
 n++;
  if(after!=0u) { after--; if(after==0u) { branch=1; break; } }
  else if(flags!=0u) after=2;
  else { count=v==prev?count+1u:1u; prev=v; if(count==3u) break; }
  rr++;
 }
 check(r+s<=1u);
 cor=correction(n,branch,h0,h1,h2,h3,h4,h5,h6,h7); check(cor!=0x80000000u);
 ex=x; ez=z; er=r; es=s; en=n; eb=branch; ec=cor;
 eh0=h0; eh1=h1; eh2=h2; eh3=h3; eh4=h4; eh5=h5; eh6=h6; eh7=h7;
}
int valid(unsigned m,unsigned q,unsigned a,unsigned fr,unsigned fk,unsigned fo,unsigned fp) {
 if(m==0u) return 1;
 if(m==1u) return q<7u && a>=1u && a<=3u;
 return m==2u && fr>=1u && fr<=3u && fk<6u && fo<10u &&
 ((fo>=2u && fo<=7u)?(fp>=1u && fp<=15u):fp==1u);
}
