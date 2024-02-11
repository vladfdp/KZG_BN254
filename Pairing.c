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

	int256 A1 = {0x1BAAA710B0759AD,0x331EC15183177FAF,0x6C0EB522D5B12278,0x4E529A5861876F6B};
	int256 A2 = {0x3B1B1355D189227D,0x79581E16F3FD90C6,0x6B887D56D5095F23,0xAAA441E3954BCF8A};
	int256 A3 = {0xDCC7B44C87CDBACF,0xF1154E7E1DA014FD,0x5ABF5CC4F49C36D4,0xE81BB482CCDF42B1};
	
	

	int256 tab[3] = {A3,A2,A1};		//(p^12-1)/r

	Fp12 ans = Fp12_one();
	Fp12 base = x;
	for (int i = 0 ; i<3; i++)
	{
		for (int j = 0; j < 256; j++)							//square and multiply
		{
			if (tab[i].u0 & 1){
				ans = Fp12_mul(ans,base);
			}
			base = Fp12_mul(base, base);
			tab[i] = shift_right_256(tab[i]);
		}
	
	}
	return ans;
}

Fp12 final_exp(Fp12 x){

	Fp12 x_inv = Fp12_inv(x);
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


Fp12 Tate_pairing(G1 P, G2 Q){

	G1 T = P;
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

