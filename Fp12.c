#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"

const int256 P2 = /**{0,0,0,104729};//{0,0,0x706,0x0f9e24e6ffdbd05d}; **/ {0x30644e72e131a029,0xb85045b68181585d,0x97816a916871ca8d,0x3c208c16d87cfd47};


Fp12 Fp12_one()
{
	
	Fp2 u1, u2;
	Fp6 v1, v2;
	Fp12 w;
	u1.x0 = Fp_one();
	u1.x1 = Fp_zero();
	u2.x0 = Fp_zero();
	u2.x1 = Fp_zero();
	v1.x0 = u1;
	v1.x1 = u2;
	v1.x2 = u2;
	v2.x0 = u2;
	v2.x1 = u2;
	v2.x2 = u2;
	w.x0 = v1;
	w.x1 = v2;
	return w;

}

Fp12 Fp12_add(Fp12 a,Fp12 b)
{
	Fp12 c;
	c.x0 = Fp6_add(a.x0,b.x0);
	c.x1 = Fp6_add(a.x1,b.x1);
	return c;
};

Fp12 Fp12_sub(Fp12 a,Fp12 b)
{
	Fp12 c;
	c.x0 = Fp6_sub(a.x0,b.x0);
	c.x1 = Fp6_sub(a.x1,b.x1);
	return c;
};

Fp12 Fp12_mul(Fp12 a,Fp12 b)
{
	Fp12 c;
	Fp6 v;
	Fp2 v1;
	Fp2 v2;
	v1.x0 = Fp_zero();
	v1.x1 = Fp_zero();
	v2.x0 = Fp_from_int(1);
	v2.x1 = Fp_zero();
	v.x0 = v1;
	v.x1 = v2;
	v.x2 = v1;
	c.x0 = Fp6_add(Fp6_mul(a.x0,b.x0), Fp6_mul(Fp6_mul(a.x1,b.x1),v));
	c.x1 = Fp6_add(Fp6_mul(a.x0,b.x1),Fp6_mul(b.x0,a.x1));
	return c; 
}

void print_Fp12(Fp12 a)
{
	print_Fp6(a.x0);printf("+ (");
	print_Fp6(a.x1);printf(") w");
}

Fp12 Fp12_exp(Fp12 base, int256 exponent)
{
	Fp12 ans = Fp12_one();

    while (exponent.u0  || exponent.u1  || exponent.u2 ||  exponent.u3 )
    {
        if (exponent.u0 & 1){
            ans = Fp12_mul(ans,base);
        }
        base = Fp12_mul(base, base);
        exponent = shift_right_256(exponent);
    }
    return ans;
    
}

Fp12 Fp12_inv(Fp12 a)
{
	int256 pmoins2;
	int256 deux = {0,0,0,2};
	Fp12 inv_a;
	pmoins2 = sub_256(P2,deux);
	inv_a = Fp12_exp(a, pmoins2);
	return inv_a;
}






