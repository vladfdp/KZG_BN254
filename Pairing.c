#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"
#include "EC.h"
#include "Pairing.h"

const long unsigned int OK = 0x8000000000000000;

Fp12 Tate_pairing(G1 P, G2 Q, int256 r)
{	
	int i = 255;
	
	while ((r.u3 && OK) == 0)
	{
		r = shift_left_256(r);
		i = i-1;
	} 
	r = shift_left_256(r);
	G1 T = P;
	Fp12 f1 = Fp12_one();
	Fp12 f2 = Fp12_one();
	Fp12 f;

	while (i)
	{	
		if (G1_equal(G1_add(T,T),G1_zero()))
		{
			f1 = Fp12_mul(f1,Fp6_to_Fp12(Fp6xFp_add(Q.x,T.x)));
		}
		else {
		Fp m = Fp_div(Fp_mul(Fp_from_int(3),Fp_mul(P.x,P.x)), (Fp_from_int(2),P.y));
		f1 = Fp12_mul(Fp12_mul(f1,f1), Fp12xFp6_add(Q.y,Fp6xFp_add(Fp6_mul_by_scalar(Fp6xFp_add(Q.x,Fp_opp(T.x)), Fp_opp(m)),Fp_opp(T.y))));
		f2 = Fp12_mul_by_Fp6(Fp12_mul(f2,f2),Fp6xFp_add(Q.x,Fp_add(Fp_add(T.x,T.x),Fp_opp(Fp_mul(m,m)))));
		T = G1_add(T,T);
		}

		if (r.u3 & OK){
		if (G1_equal(G1_add(T,P),G1_zero()))
		{
			f1 = Fp12_mul(f1,Fp6_to_Fp12(Fp6xFp_add(Q.x,T.x)));
		}
		else {
			Fp m1 = Fp_div(Fp_sub(T.y,P.y),Fp_sub(T.x, P.x));
			f1 = Fp12_mul(f1,Fp12xFp6_add(Q.y,Fp6xFp_add(Fp6_mul_by_scalar(Fp6xFp_add(Q.x,Fp_opp(T.x)), Fp_opp(m1)),Fp_opp(T.y))));
			f2 = Fp12_mul_by_Fp6(f2,Fp6xFp_add(Q.x,Fp_add(Fp_add(P.x,T.x),Fp_opp(Fp_mul(m1,m1)))));
			T = G1_add(T,P); }
		}
		r = shift_left_256(r);
		i = i-1;
	}

	f = exp_par_un_mega_int(Fp12_div(f1,f2));
	return f; 
}


Fp12 exp_par_un_mega_int(Fp12 base)
{
int256 A =  {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff};
int256 A1 = {0x2f4b6dc970      ,0x20fddadf107d20bc,0x842d43bf6369b1ff,0x6a1c71015f3f7be2};
int256 A2 = {0xe1e30a73bb94fec0,0xdaf15466b2383a5d,0x3ec3d15ad524d8f7,0x0c54efee1bd8c3b2};
int256 A3 = {0x1377e563a09a1b70,0x5887e72eceaddea3,0x790364a61f676baa,0xf977870e88d5c6c8};
int256 A4 = {0xfef0781361e443ae,0x77f5b63a2a226448,0x7f2940a8b1ddb3d1,0x5062cd0fb2015dfc};
int256 A5 = {0x6668449aed3cc48a,0x82d0d602d268c7da,0xab6a41294c0cc4eb,0xe5664568dfc50e16};
int256 A6 = {0x48a45a4a1e3a5195,0x846a3ed011a337a0,0x2088ec80e0ebae87,0x55cfe107acf3aafb};
int256 A7 = {0x40494e406f804216,0xbb10cf430b0f3785,0x6b42db8dc5514724,0xee93dfb10826f0dd};
int256 A8 = {0x4a0364b9580291d2,0xcd65664814fde37c,0xa80bb4ea44eacc5e,0x641bbadf423f9a2c};
int256 A9 = {0xbf813b8d145da900,0x29baee7ddadda71c,0x7f3811c410526294,0x5bba1668c3be69a3};
int256 A10 ={0xc230974d83561841,0xd766f9c9d570bb7f,0xbe04c7e8a6c3c760,0xc0de81def35692da};
int256 A11 ={0x361102b6b9b2b918,0x837fa97896e84abb,0x40a4efb7e54523a4,0x86964b64ca86f120};

int256 tab[11] = {A11,A10,A9,A8,A7,A6,A5,A4,A3,A2,A1};

Fp12 ans = Fp12_one();
int i;
for (i=0; i<11; i++)
{
	ans = Fp12_mul(ans,Fp12_exp(base, tab[i]));
	base = Fp12_mul(Fp12_exp(base,A),base);
}
return ans; 
}


Fp Millerloop(G1 P, G1 Q, int256 r)
{	
	int i = 255;
	
	while ((r.u3 && OK) == 0)
	{
		r = shift_left_256(r);
		i = i-1;
	} 
	r = shift_left_256(r);
	G1 T = P;
	Fp f1 = Fp_one();
	Fp f2 = Fp_one();
	Fp f;

	while (i)
	{	
		if (G1_equal(G1_add(T,T),G1_zero()))
		{
			f1 = Fp_mul(f1,Fp_add(Q.x,T.x));
		}
		else {
		Fp m = Fp_div(Fp_mul(Fp_from_int(3),Fp_mul(P.x,P.x)), (Fp_from_int(2),P.y));
		f1 = Fp_mul(Fp_mul(f1,f1), Fp_add(Q.y,Fp_add(Fp_mul(Fp_add(Q.x,Fp_opp(T.x)), Fp_opp(m)),Fp_opp(T.y))));
		f2 = Fp_mul(Fp_mul(f2,f2),Fp_add(Q.x,Fp_add(Fp_add(T.x,T.x),Fp_opp(Fp_mul(m,m)))));
		T = G1_add(T,T);
		}

		if (r.u3 & OK){
		if (G1_equal(G1_add(T,P),G1_zero()))
		{
			f1 = Fp_mul(f1,Fp_add(Q.x,T.x));
		}
		else {
			Fp m1 = Fp_div(Fp_sub(T.y,P.y),Fp_sub(T.x, P.x));
			f1 = Fp_mul(f1,Fp_add(Q.y,Fp_add(Fp_mul(Fp_add(Q.x,Fp_opp(T.x)), Fp_opp(m1)),Fp_opp(T.y))));
			f2 = Fp_mul(f2,Fp_add(Q.x,Fp_add(Fp_add(P.x,T.x),Fp_opp(Fp_mul(m1,m1)))));
			T = G1_add(T,P); }
		}
		r = shift_left_256(r);
		i = i-1;
	}
	f= Fp_div(f1,f2);
	return f;
}


Fp Weil_pairing(G1 P, G1 Q, int256 r)
{
	Fp f;
	Fp f1 = Millerloop(P,Q,r);
	Fp f2 = Millerloop(Q,P,r);
	f = Fp_opp(Fp_div(f1,f2));
	return f;
}
