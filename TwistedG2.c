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
#include "TwistedG2.h"

TwistedG2 g2_twist(g2 P){	//iso g2->TwistedG2

    Fp6 omega_squared_inv = Fp6_zero();
    Fp12 omega_cubed_inv = Fp12_zero();

    Fp a = {{0x2e9f1362305ea3ab,0x50ca36acb4f65e7f,0xa1928902b8ea8194,0x8e3855034733bbd1}};
    omega_squared_inv.x2.x0 = a;
    Fp b = {{0x20753adca9c6bfb8,0x1499be5e509e8f8f,0xf21b7c8d3cb039cf,0x1ef69c66bce9b020}};
    omega_squared_inv.x2.x1 = b;

    Fp c = {{0x2e9f1362305ea3ab,0x50ca36acb4f65e7f,0xa1928902b8ea8194,0x8e3855034733bbd1}};
    omega_cubed_inv.x1.x1.x0 = c;
    Fp d = {{0x20753adca9c6bfb8,0x1499be5e509e8f8f,0xf21b7c8d3cb039cf,0x1ef69c66bce9b020}};
    omega_cubed_inv.x1.x1.x1 = d;

    TwistedG2 ans;


    ans.x = Fp6_mul(P.x, omega_squared_inv).x0;
    ans.y = Fp12_mul(P.y, omega_cubed_inv).x0.x0;

    return ans;
}

g2 g2_untwist(TwistedG2 P){			//iso TwistedG2->g2

    Fp6 omega_squared = Fp6_zero();
    Fp12 omega_cubed = Fp12_zero();

    omega_squared.x1 = Fp2_one();
    omega_cubed.x1.x1 = Fp2_one();
    
    g2 ans;
    ans.x = Fp6_mul_by_Fp2(omega_squared, P.x);
    ans.y = Fp12_mul_by_Fp2(omega_cubed, P.y);

    return ans;

}

TwistedG2 TwistedG2_zero()
{
	TwistedG2 ans = {Fp2_zero(),Fp2_zero()};
	return ans;
} 

TwistedG2 TwistedG2_opp(TwistedG2 P0)
{
	TwistedG2 ans = {P0.x, Fp2_opp( P0.y)};
	return ans; 
}


int TwistedG2_equal(TwistedG2 P1, TwistedG2 P2)
{
	return (Fp2_equal(P1.x,P2.x) && Fp2_equal(P1.y,P2.y));

}

TwistedG2 TwistedG2_add(TwistedG2 P1, TwistedG2 P2)		//algorithme d'addition similaire a g1 et g2
{
	Fp2 m;
	TwistedG2 P;
	if (TwistedG2_equal(P1, TwistedG2_zero()))
	{
		return P2;
	}
	
	if (TwistedG2_equal(P2, TwistedG2_zero()))
	{
		return P1;
	}
	
	if (TwistedG2_equal(P1, TwistedG2_opp(P2)))
	{
		TwistedG2 ans = {Fp2_zero(),Fp2_zero()};
		return ans;
	}

	else 
	{
		if (TwistedG2_equal(P1, P2))
			{
				m = Fp2_div(Fp2_mul_by_scalar(Fp2_mul(P1.x,P1.x),Fp_from_int(3)), Fp2_mul_by_scalar(P1.y, Fp_from_int(2)));
			}
		else 
		{
			m = Fp2_div(Fp2_sub(P2.y,P1.y),Fp2_sub(P2.x,P1.x));
		}
	P.x = Fp2_sub(Fp2_sub(Fp2_mul(m,m),P1.x),P2.x);
	P.y = Fp2_sub(Fp2_mul(m, Fp2_sub(P1.x,P.x)),P1.y);
	return P;
	}
}


TwistedG2 TwistedG2_mul_by_int(TwistedG2 base, int256 exponent){		//double and add

    TwistedG2 ans = TwistedG2_zero();

    while (exponent.u0  || exponent.u1  || exponent.u2 ||  exponent.u3)
    {
        if (exponent.u0 & 1){
            ans = TwistedG2_add(ans,base);
        }
        base = TwistedG2_add(base, base);
        exponent = shift_right_256(exponent);
    }
    return ans;
}