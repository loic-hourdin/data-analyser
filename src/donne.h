#ifndef DONNE_H
#define DONNE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "liste_packet.h"
#include "liste_routeur.h"
#include "liste_flux.h"
#include "liste.h"
#include "moyenne.h"
#include "moyenne_double.h"



typedef struct
{
    double t;
    int code;
    int pid;
    int fid;
  	int tos; 		//inutil
    int bif;		//inutil
    int s;
    int d;
    int pos;
} donne;


//https://en.wikipedia.org/wiki/Standard_deviation

int** debit;
int test;


FILE *file_t_bb;
FILE *file_nbr_packet;
FILE *file_nbr_lost;
FILE *file_nbr_wait;
FILE *file_nbr_packets;


Liste_flux fluxs[SIZETABLEHASH];
Liste_packet packets[SIZETABLEHASH];
Liste_packet packets_old;
Liste_packet packets_save;
Liste_routeur routeurs;
Liste pid_read;
Liste fid_read;

//----donné globale--------
long nbrtreaty;
long nbrsend;
long nbrreceived;
long nbrflux;
long nbrlost;
long nbr_packet;
long nbr_packet_instantane;
long nbr_flux;
long nbr_routeur;
long nbr_wait;
double lostrate;
Liste lostnode;

moyenne_double moy_bb;
moyenne_double moy_timewait;
moyenne_double moy_timetrans;


int hash(long a);
void donne_maj(donne donne);
int donne_aff(donne donne);




void traitementglobal (donne donne);

#endif