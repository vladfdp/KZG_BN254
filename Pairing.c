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

const unsigned_int OK = 0x8000000000000000;
const int256 megaOK = {OK, 0, 0, 0};

Fp12 Tate_pairing(G1 P, G2 Q, int256 r)
{	
	int i = 255;
	
	while ((r & megaOK) == 0)
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
		if (equal_G1(G1_add(T,T),G1_zero))
		{
			f1 = Fp12_mul(f1,Fp6_to_Fp12(Fp6xFp_add(Q.x,T.x)));
		}
		else {
		Fp m = Fp_div(Fp_mul(Fp_from_int(3),Fp_mul(P1.x,P1.x)), (Fp_from_int(2),P1.y));
		f1 = Fp12_mul(Fp12_mul(f1,f1),Fp12_add(Fp12xFp_add(Q.y,Fp_opp(T.y),Fp6_to_Fp12(Fp6_mul_by_scalar(Fp6xFp_add(Q.x,Fp_opp(T.x),Fp_opp(m)))))));
		f2 = Fp12_mul(Fp12_mul(f2,f2),Fp6_to_Fp12(Fp6xFp_add(Q.x,Fp_add(Fp_add(T.x,T.x),Fp_opp(Fp_mul(m,m))))));
		T = G1_add(T,T);
		}

		if (r & i){
		if (equal_G1(G1_add(T,P),G1_zero))
		{
			f1 = Fp12_mul(f1,Fp6_to_Fp12(Fp6xFp_add(Q.x,T.x)));
		}
		
			f1 = Fp12_mul(Fp12_mul(f1,f1),Fp12_add(Fp12xFp_add(Q.y,Fp_opp(T.y),Fp6_to_Fp12(Fp6_mul_by_scalar(Fp6xFp_add(Q.x,Fp_opp(T.x),Fp_opp(m)))))));
			f2 = Fp12_mul(Fp12_mul(f2,f2),Fp6_to_Fp12(Fp6xFp_add(Q.x,Fp_add(Fp_add(P.x,T.x),Fp_opp(Fp_mul(m,m))))));
			T = G1_add(T,P);
		}
		r = shift_left_256(r);
		i = i-1;
	}

	f = Fp12_div(f1,f2);



}
