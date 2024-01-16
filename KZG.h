#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"

const Fp12 e_gh = {};

int verify(G1 commit, G1 proof);

G1 commit(polynomial poly);