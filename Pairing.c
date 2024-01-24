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

	f = Fp12_div(f1,f2);



}
