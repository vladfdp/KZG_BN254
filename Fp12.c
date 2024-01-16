#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"





Fp12 Fp12_zero(){
	Fp12 zero = {
		Fp6_zero(),
		Fp6_zero()
	};
	return zero;
}

Fp12 Fp12_one(){
	Fp12 one = {
		Fp6_one(),
		Fp6_zero()
	};
	return one;
}

int Fp12_equal(Fp12 a, Fp12 b){
	return (Fp6_equal(a.x0, b.x0) && Fp6_equal(a.x1, b.x1) );
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
}

Fp12 Fp12_mul_by_scalar(Fp12 x, Fp alpha){
	Fp12 ans = {
		Fp6_mul_by_scalar(x.x0,alpha),
		Fp6_mul_by_scalar(x.x1,alpha)
	};
	return ans;
}

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

Fp12 Fp12_frobenius(Fp12 x){
	return Fp12_exp(x,P);
}


Fp12 Fp12_inv(Fp12 x)
{
	Fp6 u = {
		Fp2_zero(),
		Fp2_one(),
		Fp2_zero()
	};
	Fp6 norm = Fp6_sub( Fp6_mul(x.x0,x.x0) , Fp6_mul(Fp6_mul(x.x1,x.x1),u));
	norm = Fp6_inv(norm);
	Fp12 ans = {
		Fp6_mul(x.x0, norm),
		Fp6_opp(Fp6_mul(x.x1, norm))
	};
	return ans;

}






