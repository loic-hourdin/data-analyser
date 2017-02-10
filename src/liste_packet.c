#include "liste_packet.h"

Liste_packet Packets_cons (Liste_packet l, T nvelt, packet pa){
Liste_packet p;
p = malloc(sizeof(packet_maillon));
p->donnee = nvelt;
p->suivant=l;
p->p=pa;
return(p);
}

int Packets_appartient(T x, Liste_packet l){
if ( l == NULL ) return(0);
if ( x == l->donnee ) return(1);
return(Packets_appartient(x, l->suivant));
}

Liste_packet Packets_add (Liste_packet l, T e, packet pa){
return(Packets_cons(l,e,pa));
}
Liste_packet Packets_find (Liste_packet l, T e){
	Liste_packet l_old;
	l_old=NULL;
	while (l!=NULL){
		if(l->donnee==e){
			return(l_old);
		}
		l_old=l;
		l=l->suivant;
	}
	return(l_old);
}

void Packets_free(Liste_packet *l){
	int i;
	for(i=0;i<SIZETABLEHASH;i++){
		while(l[i]!=NULL){
			Liste_packet tmp=l[i];
		l[i]=l[i]->suivant;
		free(tmp->p.routeur);
		free(tmp);
		}
	}
		
}


