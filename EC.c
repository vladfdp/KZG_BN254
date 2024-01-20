#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"
#include "EC.h"



G1 G1_opp(G1 P0)
{
	G1 ans ={P0.x, Fp_opp( P0.y)};
	return ans; 
}


int G1_equal(G1 P1, G1 P2)
{
	return (Fp_equal(P1.x,P2.x) & Fp_equal(P1.y,P2.y));

}

G1 G1_add(G1 P1, G1 P2)
{
	Fp m;
	G1 P;
	if (G1_equal(P1, G1_oppo(P2)))
	{
		G1 ans = {Fp_zero(),Fp_zero()};
		return ans;
	}

	else 
	{
		if (G1_equal(P1, P2))
			{
				m = Fp_div(Fp_mul(Fp_from_int(3),Fp_mul(P1.x,P1.x)), (Fp_from_int(2),P1.y));
			}
		else 
		{
			m = Fp_div(Fp_sub(P2.y,P1.y),Fp_sub(P2.x,P1.x));
		}
	P.x = Fp_sub(Fp_sub(Fp_mul(m,m),P1.x),P2.x);
	P.y = Fp_sub(Fp_mul(m, Fp_sub(P1.x,P.x)),P1.y);
	return P;
	}

}


G2 G2_opp(G2 P0)
{
	G2 ans ={P0.x, Fp12_sub(Fp12_zero() , P0.y)};
	return ans; 
}


int G2_equal(G2 P1, G2 P2)
{
	return (Fp12_equal(P1.x,P2.x) & Fp12_equal(P1.y,P2.y));

}

G2 G2_add(G2 P1, G2 P2)
	{
		Fp12 m;
		G2 P;
		if (G2_equal(P1, G2_opp(P2)))
		{
			G2 ans = {Fp12_zero(),Fp12_zero()};
			return ans;
		}

		else 
		{
			if (G2_equal(P1, P2))
				{
					m = Fp_div(Fp12_mul(Fp_from_int(3),Fp12_mul(P1.x,P1.x)), (Fp_from_int(2),P1.y));
				}
			else 
			{
				m = Fp12_div(Fp12_sub(P2.y,P1.y),Fp12_sub(P2.x,P1.x));
			}
		P.x = Fp12_sub(Fp12_sub(Fp12_mul(m,m),P1.x),P2.x);
		P.y = Fp12_sub(Fp12_mul(m, Fp12_sub(P1.x,P.x)),P1.y);
		return P;
		}

	}


