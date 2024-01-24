#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Fr.h"
#include "int256.h"
#include "int512.h"
#include "EC.h"

G1 G1_zero()
{
	G1 ans = {Fp_zero(),Fp_zero()};
	return ans;
} 

G2 G2_zero()
{
	G2 ans = {Fp6_zero(),Fp12_zero()};
	return ans;
} 

G1 G1_opp(G1 P0)
{
	G1 ans = {P0.x, Fp_opp( P0.y)};
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
	if (G1_equal(P1, G1_zero()))
	{
		return P2;
	}
	
	if (G1_equal(P2, G1_zero()))
	{
		return P1;
	}
	
	if (G1_equal(P1, G1_opp(P2)))
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
	return (Fp6_equal(P1.x,P2.x) & Fp12_equal(P1.y,P2.y));

}

G2 G2_add(G2 P1, G2 P2)
	{
		Fp12 m;
		G2 P;
		if (G2_equal(P1, G2_opp(P2)))
		{
			G2 ans = {Fp6_zero(),Fp12_zero()};
			return ans;
		}

		else 
		{
			if (G2_equal(P1, P2))
				{
					m = Fp12_mul_by_Fp6(Fp12_inv(Fp12_mul_by_scalar(P1.y, Fp_from_int(2))),Fp6_mul_by_scalar(Fp6_mul(P1.x,P1.x),Fp_from_int(3)));
				}
			else 
			{
				m = Fp12_mul_by_Fp6(Fp12_sub(P2.y,P1.y),Fp6_inv(Fp6_sub(P2.x,P1.x)));
			}
		P.x = Fp12_to_Fp6(Fp12xFp6_add(Fp12xFp6_add(Fp12_mul(m,m),Fp6_opp(P1.x)),Fp6_opp(P2.x)));
		P.y = Fp12_sub(Fp12_mul_by_Fp6(m, Fp6_sub(P1.x,P.x)),P1.y);
		return P;
		}

	}


G1 G1_mul_by_int(G1 base, int256 exponent){

    G1 ans = G1_zero();

    while (exponent.u0  || exponent.u1  || exponent.u2 ||  exponent.u3)
    {
        if (exponent.u0 & 1){
            ans = G1_add(ans,base);
        }
        base = G1_add(base, base);
        exponent = shift_right_256(exponent);
    }
    return ans;
}




G2 G2_mul_by_int(G2 base, int256 exponent){

    G2 ans = G2_zero();

    while (exponent.u0  || exponent.u1  || exponent.u2 ||  exponent.u3)
    {
        if (exponent.u0 & 1){
            ans = G2_add(ans,base);
        }
        base = G2_add(base, base);
        exponent = shift_right_256(exponent);
    }
    return ans;
}



