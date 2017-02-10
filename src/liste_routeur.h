#ifndef LISTE_ROUTEUR_H
#define LISTE_ROUTEUR_H

#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "moyenne_double.h"


typedef struct
{
    int num;
    int nb_lost;
    moyenne_double moy_t_wait;
    int nb_recieved;
    int nb_send;
    int nb_start;
    int nb_end;
    int nb_wait;
    FILE* f;
} routeur;



typedef long T;
typedef struct routeur_maillon *Liste_routeur;
struct routeur_maillon {
T donnee;
routeur p;
Liste_routeur suivant;
};

Liste_routeur routeurs_cons (Liste_routeur l, T nvelt, routeur routeur);
int routeurs_appartient(T x, Liste_routeur l);
Liste_routeur routeurs_add (Liste_routeur l, T e, routeur routeur);
Liste_routeur routeurs_find (Liste_routeur l, T e);
void routeurs_free(Liste_routeur l);
#endif