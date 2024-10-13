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



Fp12 final_exp_hard_part(Fp12 x){

	int256 lambda_0 = {0x30644E72E131A029,0x048B6E193FD84104,0x5CEA24F6FD736BEA,0x85989436D0F9FA91};
	int256 lambda_1 = {0x30644E72E131A029,0x048B6E193FD84105,0x3B852988DAE41FE4,0x138F3176606A30C5};
	int256 lambda_2 = {0,0,0x6F4D8248EEB859FB,0xF83E9682E87CFD46};
	
	
	Fp12 x0 = Fp12_exp(x,lambda_0);
	x = Fp12_frobenius(x);
	Fp12 x1 = Fp12_exp(x,lambda_1);
	x = Fp12_frobenius(x);
	Fp12 x2 = Fp12_exp(x,lambda_2);
	x = Fp12_frobenius(x);

	Fp12 ans = Fp12_mul(x,x0);
	ans = Fp12_mul(ans, x1);
	ans = Fp12_mul(ans, x2);
	

	return ans;
}

Fp12 final_exp(Fp12 x){

	Fp12 x_inv = Fp12_inv(x);				//on fait d'abord la partie facile
	for (int i = 0; i < 6; i++)
	{
		x = Fp12_frobenius(x);
	}
	x = Fp12_mul(x,x_inv);
	Fp12 x1 = x;
	x = Fp12_frobenius(x);
	x = Fp12_frobenius(x);
	x = Fp12_mul(x, x1);

	return final_exp_hard_part(x);
	
}


Fp12 Tate_pairing(g1 P, g2 Q){

	g1 T = P;
	Fp12 f = Fp12_one();

	int256 r = shift_left_256(shift_left_256(shift_left_256(R)));

	for (int i = 0; i < 253; i++)										//Miller loop
	{
		Fp x_sq_times_a = Fp_mul( Fp_mul(T.x, T.x), Fp_from_int(3) );
		Fp y2 = Fp_mul(T.y, Fp_from_int(2));
		Fp slope = Fp_div(x_sq_times_a, y2);
		Fp slope_sq = Fp_mul(slope, slope);

		Fp x_2T = Fp_sub(slope_sq, Fp_mul(T.x, Fp_from_int(2)));

		Fp slope_times_dif = Fp_mul(slope, Fp_sub(T.x, x_2T));

		Fp y_2T = Fp_sub(slope_times_dif, T.y);

		Fp6 x_dif = Fp6xFp_add(Q.x, Fp_opp(T.x));
		Fp12 y_dif = Fp12xFp_add(Q.y, Fp_opp(T.y));

		Fp6 slope_times_x_dif = Fp6_mul_by_scalar(x_dif, slope);
		Fp12 l_TT = Fp12xFp6_add(y_dif, Fp6_opp(slope_times_x_dif));

		f = Fp12_mul(f,f);
		f = Fp12_mul(f,l_TT);

		T.x = x_2T;
		T.y = y_2T;
		

		if (r.u3 & 0x8000000000000000)
		{
			

			slope = Fp_div( Fp_sub(T.y, P.y), Fp_sub(T.x, P.x));		//dans la derniere iteration on divise par zero
			slope_sq = Fp_mul(slope, slope);							//ce n'est pas un probleme du a la facon dont l'inversion est codé
																		// comme inv(0) = 0 on obtient exactement le resultat voulu
			Fp x_TP = Fp_sub( Fp_sub(slope_sq, T.x), P.x);

			slope_times_dif = Fp_mul(slope, Fp_sub(T.x, x_TP));
			Fp y_TP = Fp_sub(slope_times_dif, T.y);

		 	x_dif = Fp6xFp_add(Q.x, Fp_opp(T.x));
			y_dif = Fp12xFp_add(Q.y, Fp_opp(T.y));

			slope_times_x_dif = Fp6_mul_by_scalar(x_dif, slope);
			Fp12 l_TP = Fp12xFp6_add(y_dif, Fp6_opp(slope_times_x_dif));

			f = Fp12_mul(f, l_TP);
			T.x = x_TP;
			T.y = y_TP;
		}
		r = shift_left_256(r);
		
	}


	return final_exp(f);
	
}

