#ifndef LISTE_PACKET_H
#define LISTE_PACKET_H

#include <stdio.h>
#include <stdlib.h>
#include "moyenne_double.h"
#include "liste.h"


#ifndef SIZETABLEHASH
#define SIZETABLEHASH 100
#endif

typedef struct
{
    int pid;
    int s;
    int d;
    int pos;
    int destroy;
    int taille;
    double t_start;
    double t_start_wait;
    double t_start_trans;
    double t_wait;
    double t_end;
    moyenne_double moy_t_trans;
    moyenne_double moy_t_wait;
    Liste routeur;
} packet;


typedef long T;
typedef struct packet_maillon packet_maillon;
struct packet_maillon {
T donnee;
packet p;
packet_maillon* suivant;
};

typedef packet_maillon* Liste_packet;

Liste_packet Packets_cons (Liste_packet l, T nvelt, packet packet);
int Packets_appartient(T x, Liste_packet l);
Liste_packet Packets_add (Liste_packet l, T e, packet packet);
Liste_packet Packets_find (Liste_packet l, T e);
void Packets_free(Liste_packet *l);

#endif