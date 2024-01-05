#include <stdio.h>
#include <stdlib.h>
#include <extension.h>

#define p 17
#define k 12

typedef struct Fp2 Fp2;
struct Fp2
{
	Fp.x;
	Fp.y;
};

Fp2 Fp2_add(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x = Fp_add(a.x,b.x);
	c.y = Fp_add(a.y,b.y);
	return c;
}

Fp2 Fp2_mult(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x = Fp_sub(Fp_mult(a.x, b.x),Fp_mult(a.y,b.y));
	c.y = Fp_add(Fp_mult(a.x,b.y),Fp_mult(b.x,a.y));
	return c;
}

Fp2 Fp2_sub(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x = Fp_sub(a.x,b.x);
	c.y = Fp_sub(a.y,b.y);
	return c;
}

typedef struct Fp6 Fp6;
struct Fp6
{
	Fp2.x;
	Fp2.y;
	Fp2.z;
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

Fp6_mult(Fp6 a, Fp6 b)
{
	Fp6 c;
	Fp2 d;
	d.x = 9;
	d.y = u;
	c.x = Fp2_add(Fp2_mult(a.x,b.x), Fp2_mult(d,Fp2_add(Fp2_mult(a.z,b.y),Fp2_mult(a.y,b.z))));
	c.y = Fp2_add(Fp2_add(Fp2_mult(a.x,b.y),Fp2_mult(a.y,b.x)),Fp2_mult(d,Fp2_mult(a.z,b.z)));
	c.z = Fp2_add(Fp2_mult(a.y,b.y),Fp2_mult(a.z,b.x));
	return c;
}

typedef struct Fp12 Fp12;
struct Fp12
{
	Fp12.x;
	Fp12.y;
};


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

Fp12 Fp12_mult(a.y,b.y)
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
	c.x = Fp6_add(Fp6_mult(a.x,b.x), Fp6_mult(Fp6_mult(a.y,b.y),v));
	c.y = Fp6_add(Fp6_mult(a.x,b.y),Fp6_mult(b.x,a.y));
	return c; 
}
