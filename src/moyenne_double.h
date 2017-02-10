#ifndef MOYENNE_DOUBLE_H
#define MOYENNE_DOUBLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//https://en.wikipedia.org/wiki/Standard_deviation
typedef struct
{
    double a;
    double q;
    double k;
} moyenne_double;



moyenne_double new_moy_double();
moyenne_double moyenne_double_maj(moyenne_double moy,double x);
double moyenne_double_ec(moyenne_double moy);
double moyenne_double_moy(moyenne_double moy);
void moyenne_double_ic(moyenne_double moy, double* ic0, double* ic1);
double moyenne_double_ic_plus(moyenne_double moy);
double moyenne_double_ic_moin(moyenne_double moy);














#endif