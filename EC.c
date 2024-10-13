#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Fr.h"
#include "int256.h"
#include "int512.h"
#include "TwistedG2.h"
#include "EC.h"

g1 g1_zero()
{
	g1 ans = {Fp_zero(),Fp_zero()};
	return ans;
} 

g2 g2_zero()
{
	g2 ans = {Fp6_zero(),Fp12_zero()};
	return ans;
} 

g1 g1_opp(g1 P0)
{
	g1 ans = {P0.x, Fp_opp( P0.y)};
	return ans; 
}


int g1_equal(g1 P1, g1 P2)
{
	return (Fp_equal(P1.x,P2.x) && Fp_equal(P1.y,P2.y));

}

g1 g1_add(g1 P1, g1 P2)
{
	Fp m;
	g1 P;
	if (g1_equal(P1, g1_zero()))
	{
		return P2;
	}
	
	if (g1_equal(P2, g1_zero()))
	{
		return P1;
	}
	
	if (g1_equal(P1, g1_opp(P2)))
	{
		g1 ans = {Fp_zero(),Fp_zero()};
		return ans;
	}

	else 
	{
		if (g1_equal(P1, P2))
			{
				m = Fp_div(Fp_mul(Fp_from_int(3),Fp_mul(P1.x,P1.x)), Fp_mul(Fp_from_int(2),P1.y)); //tangeante au point
			}
		else 
		{
			m = Fp_div(Fp_sub(P2.y,P1.y),Fp_sub(P2.x,P1.x));									//droite passant par les deux points	
		}
	P.x = Fp_sub(Fp_sub(Fp_mul(m,m),P1.x),P2.x);				//nouvelle coordonnées
	P.y = Fp_sub(Fp_mul(m, Fp_sub(P1.x,P.x)),P1.y);
	return P;
	}
}


g2 g2_opp(g2 P0)
{
	g2 ans ={P0.x, Fp12_sub(Fp12_zero() , P0.y)};
	return ans; 
}


int g2_equal(g2 P1, g2 P2)
{
	return (Fp6_equal(P1.x,P2.x) & Fp12_equal(P1.y,P2.y));

}

g2 g2_add(g2 P1, g2 P2)
	{
		Fp12 m;
		g2 P;
		if (g2_equal(P1, g2_zero()))
		{
			return P2;
		}
	
		if (g2_equal(P2, g2_zero()))
		{
			return P1;
		}

		if (g2_equal(P1, g2_opp(P2)))
		{
			g2 ans = {Fp6_zero(),Fp12_zero()};
			return ans;
		}
		else 
		{
			if (g2_equal(P1, P2))
				{
					m = Fp12_mul_by_Fp6(Fp12_inv(Fp12_mul_by_scalar(P1.y, Fp_from_int(2))) , Fp6_mul_by_scalar(Fp6_mul(P1.x,P1.x),Fp_from_int(3)));		//tangeante
				}
			else 
			{
				m = Fp12_mul_by_Fp6(Fp12_sub(P2.y,P1.y),Fp6_inv(Fp6_sub(P2.x,P1.x)));				//droite
			}
		P.x = Fp12_to_Fp6(Fp12xFp6_add(Fp12_mul(m,m),Fp6_add(Fp6_opp(P1.x),Fp6_opp(P2.x))));		//nouvelle coord
		P.y = Fp12_sub(Fp12_mul_by_Fp6(m, Fp6_sub(P1.x,P.x)),P1.y);
		return P;
		}

	}


g1 g1_mul_by_int(g1 base, int256 exponent){		//double and add

    g1 ans = g1_zero();

    while (exponent.u0  || exponent.u1  || exponent.u2 ||  exponent.u3)
    {
        if (exponent.u0 & 1){
            ans = g1_add(ans,base);
        }
        base = g1_add(base, base);
        exponent = shift_right_256(exponent);
    }
    return ans;
}


g2 g2_mul_by_int(g2 base, int256 exponent){		//double and add

    g2 ans = g2_zero();

    while (exponent.u0  || exponent.u1  || exponent.u2 ||  exponent.u3)
    {
        if (exponent.u0 & 1){
            ans = g2_add(ans,base);
        }
        base = g2_add(base, base);
        exponent = shift_right_256(exponent);
    }
    return ans;
}

g2 g2_frobenius(g2 A)
{	
	g2 B;
	B.x = Fp6_frobenius(A.x);
	B.y = Fp12_frobenius(A.y);
	return B;
}

g2 g2_mul_by_int_twist(g2 base, int256 exponent){ //equivalent a g2_mul_by_int, plus rapide

	TwistedG2 t_base = g2_twist(base);							//on transforme le point en TwistedG2
	TwistedG2 t_ans = TwistedG2_mul_by_int(t_base, exponent);	//on fait un double-and-add dans TwistedG2
	return g2_untwist(t_ans);									//on retransforme en point de g2
}

void print_g1(g1 P)
{
	printf("(");
	print_Fp(P.x); printf(",");
	print_Fp(P.y); printf(")\n");
}

void print_g2(g2 P)
{
	printf("(");
	print_Fp6(P.x); printf(",");
	print_Fp12(P.y); printf(")\n");
}



int g2_is_on_curve(g2 P){		//verifie qu'un couple est bien sur la courbe

	if (Fp6_is_zero(P.x) && Fp12_is_zero(P.y))
	{
		return 1;
	}
	
	Fp12 y_sq = Fp12_mul(P.y, P.y);
	Fp6 fx = Fp6_mul(P.x,Fp6_mul(P.x,P.x));
	fx = Fp6xFp_add(fx, Fp_from_int(3));

	Fp12 ans = Fp12xFp6_add(y_sq, Fp6_opp(fx));		//on calcule juste y^2 - x^3 - 3

	return Fp12_is_zero(ans);						//verifie que c'est bien nul
}