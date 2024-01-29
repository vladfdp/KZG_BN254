#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "int256.h"
#include "int512.h"

Fp2 Fp2_zero(){
	Fp2 zero = {
		Fp_zero(),
		Fp_zero()
	};
	return zero;
}

int Fp2_is_zero(Fp2 x){
	return Fp_is_zero(x.x0) && Fp_is_zero(x.x1);
}

Fp2 Fp2_one(){
	Fp2 one = {
		Fp_one(),
		Fp_zero()
	};
	return one;
}

int Fp2_equal(Fp2 a, Fp2 b){
	return (Fp_equal(a.x0, b.x0) && Fp_equal(a.x1, b.x1) );
}

Fp2 Fp2_from_int(uint64_t a, uint64_t b){
	Fp2 ans = {Fp_from_int(a), Fp_from_int(b)};
    return ans;
}

Fp2 Fp2_add(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x0 = Fp_add(a.x0,b.x0);
	c.x1 = Fp_add(a.x1,b.x1);
	return c;
}

Fp2 Fp2_mul(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x0 = Fp_sub(Fp_mul(a.x0, b.x0), Fp_mul(a.x1,b.x1));
	c.x1 = Fp_add(Fp_mul(a.x0,b.x1),Fp_mul(b.x0,a.x1));
	return c;
}

Fp2 Fp2_mul_by_scalar(Fp2 x, Fp alpha){
	Fp2 ans = {
		Fp_mul(x.x0,alpha),
		Fp_mul(x.x1,alpha)
	};
	return ans;
}

Fp2 Fp2_sub(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x0 = Fp_sub(a.x0,b.x0);
	c.x1 = Fp_sub(a.x1,b.x1);
	return c;
}

Fp2 Fp2_opp(Fp2 x){
	Fp2 ans = {
		Fp_opp(x.x0),
		Fp_opp(x.x1)
	};
	return ans;
}

Fp2 Fp2_inv(Fp2 x){
	Fp norm = Fp_add( Fp_mul(x.x0, x.x0), Fp_mul(x.x1, x.x1));
	Fp norm_inv = Fp_inv(norm);
	Fp2 ans = {
		Fp_mul(x.x0, norm_inv),
		Fp_opp(Fp_mul(x.x1, norm_inv))
	};
	return ans;
}

Fp2 Fp2_div(Fp2 a, Fp2 b){
	return Fp2_mul(a, Fp2_inv(b));
}

void print_Fp2 (Fp2 a)
{
	print_Fp(a.x0);
	printf("+");
	print_Fp(a.x1);
	printf("u");
}
