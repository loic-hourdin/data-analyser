#ifndef LISTE_FLUX_H
#define LISTE_FLUX_H

#include <stdio.h>
#include <stdlib.h>

#include "moyenne_double.h"

#ifndef SIZETABLEHASH
#define SIZETABLEHASH 100
#endif

typedef struct
{
    int fid;
    int nb_send;
    int nb_recieved;
    int nb_lost;
    double t_start;
    double t_life;
    moyenne_double moy_d_send;
    moyenne_double moy_t_recieved;
    moyenne_double moy_t_acheminement;
} flux;


typedef long T;
typedef struct flux_maillon *Liste_flux;
struct flux_maillon {
T donnee;
flux p;
Liste_flux suivant;
};

Liste_flux fluxs_cons (Liste_flux l, T nvelt, flux flux);
int fluxs_appartient(T x, Liste_flux l);
Liste_flux fluxs_add (Liste_flux l, T e, flux flux);
Liste_flux fluxs_find (Liste_flux l, T e);
void fluxs_free(Liste_flux *l);

#endif