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

int Fp12_is_zero(Fp12 x){
	return Fp6_is_zero(x.x0) && Fp6_is_zero(x.x0);
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

	x.x0 = Fp6_frobenius(x.x0);

	Fp2 t;
	Fp tx0 = {{0x1284b71c2865a7df,0xe8b99fdd76e68b60,0x5c521e08292f2176,0xd60b35dadcc9e470}};
	Fp tx1 = {{0x246996f3b4fae7e6,0xa6327cfe12150b8e,0x747992778eeec7e5,0xca5cf05f80f362ac}};

	t.x0 = tx0;
	t.x1 = tx1;

	x.x1 = Fp6_mul_by_Fp2(Fp6_frobenius(x.x1), t);

	return x;
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

Fp12 Fp12_div(Fp12 a,Fp12 b)
{	
	Fp12 ans = Fp12_mul(a, Fp12_inv(b));
	return ans;
}

Fp12 Fp12_mul_by_Fp6(Fp12 a, Fp6 b)
{	
	Fp12 c;
	c.x0 = Fp6_mul(a.x0,b);
	c.x1 = Fp6_mul(a.x1,b);
	return c;
}


Fp6 Fp12_to_Fp6(Fp12 a)
{
	return a.x0;
}


Fp12 Fp6_to_Fp12(Fp6 a)
{
	Fp12 b;
	b.x0 = a;
	b.x1 = Fp6_zero();
	return b;
}

Fp12 Fp12xFp_add(Fp12 a,Fp b)
{
	a.x0 = Fp6xFp_add(a.x0,b);
	return a;
}

Fp12 Fp12xFp6_add(Fp12 a, Fp6 b)
{
	a.x0 = Fp6_add(a.x0,b);
	return a;
}

Fp12 Fp12_mul_by_Fp2(Fp12 a,Fp2 b)
{
	Fp12 c = { {Fp2_mul((a.x0).x0,b),Fp2_mul((a.x0).x1,b),Fp2_mul((a.x0).x2,b)} , {Fp2_mul((a.x1).x0,b),Fp2_mul((a.x1).x1,b),Fp2_mul((a.x1).x2,b)} };
	return c;
}




