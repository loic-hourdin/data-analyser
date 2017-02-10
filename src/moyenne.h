#ifndef MOYENNE_H
#define MOYENNE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//https://en.wikipedia.org/wiki/Standard_deviation
typedef struct
{
    long a;
    long q;
    long k;
} moyenne;



moyenne new_moy();
moyenne moyenne_maj(moyenne moy,long x);
long moyenne_ec(moyenne moy);
long moyenne_moy(moyenne moy);
void moyenne_ic(moyenne moy, long* ic0, long* ic1);














#endif