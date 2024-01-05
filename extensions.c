#include <stdio.h>
#include <stdlib.h>
#include "extensions.h"
#include "Fp.h"
#include "int256.h"
#include "int512.h"


#define p 17
#define k 12



Fp2 Fp2_add(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x = Fp_add(a.x,b.x);
	c.y = Fp_add(a.y,b.y);
	return c;
}

Fp2 Fp2_mul(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x = Fp_sub(Fp_mul(a.x, b.x),Fp_mul(a.y,b.y));
	c.y = Fp_add(Fp_mul(a.x,b.y),Fp_mul(b.x,a.y));
	return c;
}

Fp2 Fp2_sub(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x = Fp_sub(a.x,b.x);
	c.y = Fp_sub(a.y,b.y);
	return c;
}


Fp6 Fp6_add(Fp6 a,Fp6 b)
{
	Fp6 c;
	c.x = Fp2_add(a.x,b.x);
	c.y = Fp2_add(a.y,b.y);
	c.z = Fp2_add(a.z,b.z);
	return c;
}

Fp6 Fp6_sub(Fp6 a,Fp6 b)
{
	Fp6 c;
	c.x = Fp2_sub(a.x,b.x);
	c.y = Fp2_sub(a.y,b.y);
	c.z = Fp2_sub(a.z,b.z);
	return c;
}

Fp6_mul(Fp6 a, Fp6 b)
{
	Fp6 c;
	Fp2 d;
	d.x = 9;
	d.y = u;
	c.x = Fp2_add(Fp2_mul(a.x,b.x), Fp2_mul(d,Fp2_add(Fp2_mul(a.z,b.y),Fp2_mul(a.y,b.z))));
	c.y = Fp2_add(Fp2_add(Fp2_mul(a.x,b.y),Fp2_mul(a.y,b.x)),Fp2_mul(d,Fp2_mul(a.z,b.z)));
	c.z = Fp2_add(Fp2_mul(a.y,b.y),Fp2_mul(a.z,b.x));
	return c;
}




Fp12 Fp12_add(Fp12 a,Fp12 b)
{
	Fp12 c;
	c.x = Fp6_add(a.x,b.x);
	c.y = Fp6_add(a.y,b.y);
	return c;
};

Fp12 Fp12_sub(Fp12 a,Fp12 b)
{
	Fp12 c;
	c.x = Fp6_sub(a.x,b.x);
	c.y = Fp6_sub(a.y,b.y);
	return c;
};

Fp12 Fp12_mul(a.y,b.y)
{
	Fp12 c;
	Fp6 v;
	Fp2 v1;
	Fp2 v2;
	v1.x = 0;
	v1.y = 0;
	v2.x = 1;
	v2.y = 0;
	v.x = v1;
	v.y = v2;
	c.x = Fp6_add(Fp6_mul(a.x,b.x), Fp6_mul(Fp6_mul(a.y,b.y),v));
	c.y = Fp6_add(Fp6_mul(a.x,b.y),Fp6_mul(b.x,a.y));
	return c; 
}
