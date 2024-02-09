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





Fp12 final_exp(Fp12 x)
{

	int256 A1 = {0x2f4b6dc970	   ,0x20fddadf107d20bc,0x842d43bf6369b1ff,0x6a1c71015f3f7be2};
	int256 A2 = {0xe1e30a73bb94fec0,0xdaf15466b2383a5d,0x3ec3d15ad524d8f7,0x0c54efee1bd8c3b2};
	int256 A3 = {0x1377e563a09a1b70,0x5887e72eceaddea3,0x790364a61f676baa,0xf977870e88d5c6c8};
	int256 A4 = {0xfef0781361e443ae,0x77f5b63a2a226448,0x7f2940a8b1ddb3d1,0x5062cd0fb2015dfc};
	int256 A5 = {0x6668449aed3cc48a,0x82d0d602d268c7da,0xab6a41294c0cc4eb,0xe5664568dfc50e16};
	int256 A6 = {0x48a45a4a1e3a5195,0x846a3ed011a337a0,0x2088ec80e0ebae87,0x55cfe107acf3aafb};
	int256 A7 = {0x40494e406f804216,0xbb10cf430b0f3785,0x6b42db8dc5514724,0xee93dfb10826f0dd};
	int256 A8 = {0x4a0364b9580291d2,0xcd65664814fde37c,0xa80bb4ea44eacc5e,0x641bbadf423f9a2c};
	int256 A9 = {0xbf813b8d145da900,0x29baee7ddadda71c,0x7f3811c410526294,0x5bba1668c3be69a3};
	int256 A10 = {0xc230974d83561841,0xd766f9c9d570bb7f,0xbe04c7e8a6c3c760,0xc0de81def35692da};
	int256 A11 = {0x361102b6b9b2b918,0x837fa97896e84abb,0x40a4efb7e54523a4,0x86964b64ca86f120};

	int256 tab[11] = {A11,A10,A9,A8,A7,A6,A5,A4,A3,A2,A1};		//(p^12-1)/r

	Fp12 ans = Fp12_one();
	Fp12 base = x;
	for (int i = 0 ; i<10; i++)
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

	for (int j = 0; j < 230; j++)
		{
			if (tab[10].u0 & 1){
				ans = Fp12_mul(ans,base);
			}
			base = Fp12_mul(base, base);
			tab[10] = shift_right_256(tab[10]);
		}
	

	return ans; 
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

