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
	return (Fp_equal(P1.x,P2.x) && Fp_equal(P1.y,P2.y));

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
		if (G2_equal(P1, G2_zero()))
		{
			return P2;
		}
	
		if (G2_equal(P2, G2_zero()))
		{
			return P1;
		}

		if (G2_equal(P1, G2_opp(P2)))
		{
			G2 ans = {Fp6_zero(),Fp12_zero()};
			return ans;
		}
		else 
		{
			if (G2_equal(P1, P2))
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


G1 G1_mul_by_int(G1 base, int256 exponent){		//double and add

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


G2 G2_mul_by_int(G2 base, int256 exponent){		//double and add

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

G2 G2_frobenius(G2 A)
{	
	G2 B;
	B.x = Fp6_frobenius(A.x);
	B.y = Fp12_frobenius(A.y);
	return B;
}

G2 G2_mul_by_int_twist(G2 base, int256 exponent){ //equivalent a G2_mul_by_int, plus rapide

	TwistedG2 t_base = G2_twist(base);							//on transforme le point en TwistedG2
	TwistedG2 t_ans = TwistedG2_mul_by_int(t_base, exponent);	//on fait un double-and-add dans TwistedG2
	return G2_untwist(t_ans);									//on retransforme en point de G2
}

void print_G1(G1 P)
{
	printf("(");
	print_Fp(P.x); printf(",");
	print_Fp(P.y); printf(")\n");
}

void print_G2(G2 P)
{
	printf("(");
	print_Fp6(P.x); printf(",");
	print_Fp12(P.y); printf(")\n");
}



int G2_is_on_curve(G2 P){		//verifie qu'un couple est bien sur la courbe

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