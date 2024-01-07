#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"




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
	c.x0 = Fp6_add(Fp6_mul(a.x0,b.x0), Fp6_mul(Fp6_mul(a.x1,b.x1),v));
	c.x1 = Fp6_add(Fp6_mul(a.x0,b.x1),Fp6_mul(b.x0,a.x1));
	return c; 
}

void print_Fp12(Fp12 a)
{
	print_Fp6(a.x0);printf("+ (");
	print_Fp6(a.x1);printf(") w");
}