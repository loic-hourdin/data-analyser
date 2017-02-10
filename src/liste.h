#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>
#include <stdlib.h>


typedef long T;
typedef struct maillon *Liste;
struct maillon {
T donnee;
Liste suivant;
};

Liste cons (Liste l, T nvelt);
int appartient(T x, Liste l);
Liste add (Liste l, T e);
void affiche (Liste l);
int position (Liste l, T e);
int nombre (Liste l, T e);
int sommeite(Liste l);
int sommerec(Liste l);
Liste recopie(Liste l);
void free_liste(Liste l);


#endif