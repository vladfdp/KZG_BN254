#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"
#include "Pairing.h"



EFp EFp_oppo(EFp P0)
{
	EFp ans ={P0.x0, Fp_sub(Fpzero() , P0.x1)};
	return ans; 
}


int EFp_is_equal(P1, P2)
{
	return (Fp_is_equal(P1.x0,P2.x0) & Fp_is_equal(P1.x1,P2.x1));

}

EFp EFp_add(EFp12 P1, EFp12 P2)
	{
		Fp12 m;
		EFp12 P;
		if (EFp_is_equal(P1, EFp_oppo(P2)))
		{
			return {Fp12zero(),Fp12zero()};
		}

		else 
		{
			if (EFp_is_equal(P1, P2))
				{
					m = Fp_div(Fp_mul(Fp_from_int(3),Fp_mul(P1.x0,P1.x0)), (Fp_from_int(2),P1.x1));
				}
			else 
			{
				m = Fpdiv(Fp_sub(P2.x1,P1.x1),Fp_sub(P2.x0,P1.x0));
			}
		P.x0 = Fp_sub(Fp_sub(Fp_mul(m,m),P1.x0),P2.x0);
		P.x1 = Fp_sub(Fp_mul(m, Fp_sub(P1.x0,P.x0)),P1.x1);
		return P;
		}

	}


	EFp12 EFp12_oppo(EFp P0)
{
	EFp12 ans ={P0.x0, Fp12_sub(Fp12zero() , P0.x1)};
	return ans; 
}


int EFp12_is_equal(P1, P2)
{
	return (Fp12_is_equal(P1.x0,P2.x0) & Fp12_is_equal(P1.x1,P2.x1));

}

EFp EFp12_add(EFp P1, EFp P2)
	{
		Fp12 m;
		EFp12 P;
		if (EFp12_is_equal(P1, EFp12_oppo(P2)))
		{
			return {Fp12zero(),Fp12zero()};
		}

		else 
		{
			if (EFp12_is_equal(P1, P2))
				{
					m = Fp_div(Fp12_mul(Fp12trois(),Fp12_mul(P1.x0,P1.x0)), (Fp12deux(),P1.x1));
				}
			else 
			{
				m = Fp12div(Fp12_sub(P2.x1,P1.x1),Fp12_sub(P2.x0,P1.x0));
			}
		P.x0 = Fp12_sub(Fp12_sub(Fp12_mul(m,m),P1.x0),P2.x0);
		P.x1 = Fp12_sub(Fp12_mul(m, Fp12_sub(P1.x0,P.x0)),P1.x1);
		return P;
		}

	}


	