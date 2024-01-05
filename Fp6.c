#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "int256.h"
#include "int512.h"


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

Fp6 Fp6_mul(Fp6 a, Fp6 b)
{
	Fp6 c;
	Fp2 d;
	d.x0 = Fp_from_int(9);
	d.x1 = Fp_from_int(1);
	c.x0 = Fp2_add(Fp2_mul(a.x0,b.x0), Fp2_mul(d,Fp2_add(Fp2_mul(a.x2,b.x1),Fp2_mul(a.x1,b.x2))));
	c.x1 = Fp2_add(Fp2_add(Fp2_mul(a.x0,b.x1),Fp2_mul(a.x1,b.x0)),Fp2_mul(d,Fp2_mul(a.x2,b.x2)));
	c.x2 = Fp2_add(Fp2_mul(a.x1,b.x1),Fp2_mul(a.x2,b.x0));
	return c;
}