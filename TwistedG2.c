#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Fr.h"
#include "int256.h"
#include "int512.h"
#include "EC.h"
#include "TwistedG2.h"

TwistedG2 G2_twist(G2 P);

G2 G2_untwist(TwistedG2 P);