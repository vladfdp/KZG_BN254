#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "int256.h"
#include "int512.h"

Fp6 Fp6_zero(){
	Fp6 zero = {
		Fp2_zero(),
		Fp2_zero(),
		Fp2_zero()
	};
	return zero;
}

Fp6_is_zero(Fp6 x){
	return Fp2_is_zero(x.x0) && Fp2_is_zero(x.x1) && Fp2_is_zero(x.x2);
}

Fp6 Fp6_one(){
	Fp6 one = {
		Fp2_one(),
		Fp2_zero(),
		Fp2_zero()
	};
	return one;
}

int Fp6_equal(Fp6 a, Fp6 b){
	return (Fp2_equal(a.x0, b.x0) && Fp2_equal(a.x1, b.x1) && Fp2_equal(a.x2, b.x2));
}


Fp6 Fp6_add(Fp6 a,Fp6 b)
{
	Fp6 c;
	c.x0 = Fp2_add(a.x0,b.x0);
	c.x1 = Fp2_add(a.x1,b.x1);
	c.x2 = Fp2_add(a.x2,b.x2);
	return c;
}

Fp6 Fp6_sub(Fp6 a,Fp6 b)
{
	Fp6 c;
	c.x0 = Fp2_sub(a.x0,b.x0);
	c.x1 = Fp2_sub(a.x1,b.x1);
	c.x2 = Fp2_sub(a.x2,b.x2);
	return c;
}

Fp6 Fp6_opp(Fp6 x){
	Fp6 ans = {
		Fp2_opp(x.x0),
		Fp2_opp(x.x1),
		Fp2_opp(x.x2),
	};
	return ans;
}

Fp6 Fp6_mul(Fp6 a, Fp6 b)
{
	Fp6 c;
	Fp2 d;
	d.x0 = Fp_from_int(9);
	d.x1 = Fp_from_int(1);
	c.x0 = Fp2_add(Fp2_mul(a.x0,b.x0), Fp2_mul(d,Fp2_add(Fp2_mul(a.x2,b.x1),Fp2_mul(a.x1,b.x2))));
	c.x1 = Fp2_add(Fp2_add(Fp2_mul(a.x0,b.x1),Fp2_mul(a.x1,b.x0)),Fp2_mul(d,Fp2_mul(a.x2,b.x2)));
	c.x2 = Fp2_add(Fp2_add(Fp2_mul(a.x1,b.x1),Fp2_mul(a.x2,b.x0)),Fp2_mul(a.x0,b.x2));
	return c;
}

Fp6 Fp6_mul_by_scalar(Fp6 x, Fp alpha){
	Fp6 ans = {
		Fp2_mul_by_scalar(x.x0, alpha),
		Fp2_mul_by_scalar(x.x1, alpha),
		Fp2_mul_by_scalar(x.x2, alpha),
	};
	return ans;
}

Fp6 Fp6_mul_by_Fp2(Fp6 a, Fp2 b){
	Fp6 ans = {
		Fp2_mul(a.x0, b),
		Fp2_mul(a.x1, b),
		Fp2_mul(a.x2, b),
	};
	return ans;
}

Fp6 Fp6_inv(Fp6 x){

	Fp2 f = Fp2_from_int(9,1);
	
	Fp2 a2 = Fp2_mul(x.x2,x.x2);
	Fp2 b2 = Fp2_mul(x.x1,x.x1);
	Fp2 c2 = Fp2_mul(x.x0,x.x0);

	Fp2 af = Fp2_mul(x.x2, f);
	Fp2 bc = Fp2_mul(x.x1, x.x0);

	Fp2 D1 = Fp2_mul( Fp2_mul(a2 , af), f );
	Fp2 D2 = Fp2_mul_by_scalar( Fp2_mul( bc, af) ,Fp_from_int(3));
	Fp2 D3 = Fp2_mul( Fp2_mul(b2, x.x1), f);
	Fp2 D4 = Fp2_mul(c2, x.x0);

	Fp2 K = Fp2_add( Fp2_sub(D1,D2), Fp2_add(D3, D4) );
	K = Fp2_inv(K);

	Fp2 T0 = Fp2_sub(c2 , Fp2_mul(af, x.x1));
	Fp2 T1 = Fp2_sub(Fp2_mul(a2,f), bc);
	Fp2 T2 = Fp2_sub(b2, Fp2_mul(x.x0, x.x2));

	Fp6 ans = {
		Fp2_mul(T0,K),
		Fp2_mul(T1,K),
		Fp2_mul(T2,K)
	};
	return ans;
}

Fp6 Fp6xFp_add(Fp6 a, Fp b)
{
	a.x0.x0 = Fp_add(a.x0.x0, b);
	return a;
}

void print_Fp6(Fp6 a)
{
	print_Fp2(a.x0); printf("+ (");
	print_Fp2(a.x1); printf(") v + (");
	print_Fp2(a.x2); printf (") v^2");
}

Fp6 Fp6_exp(Fp6 base, int256 exponent)
{
	Fp6 ans = Fp6_one();

    while (exponent.u0  || exponent.u1  || exponent.u2 ||  exponent.u3)
    {
        if (exponent.u0 & 1){
            ans = Fp6_mul(ans,base);
        }
        base = Fp6_mul(base, base);
        exponent = shift_right_256(exponent);
    }
    return ans;
}

 Fp6 Fp6_frobenius(Fp6 x){
	return Fp6_exp(x,P);
}
