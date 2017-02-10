#include "liste_flux.h"

Liste_flux fluxs_cons (Liste_flux l, T nvelt, flux pa){
Liste_flux p;
p = malloc(sizeof(struct flux_maillon));
p->donnee = nvelt;
p->suivant=l;
p->p=pa;
return(p);
}

int fluxs_appartient(T x, Liste_flux l){
if ( l == NULL ) return(0);
if ( x == l->donnee ) return(1);
return(fluxs_appartient(x, l->suivant));
}

Liste_flux fluxs_add (Liste_flux l, T e, flux pa){
return(fluxs_cons(l,e,pa));
}
Liste_flux fluxs_find (Liste_flux l, T e){
	while (l!=NULL){
		if(l->donnee==e){
			return(l);
		}
		l=l->suivant;
	}
	return(l);
}
void fluxs_free(Liste_flux *l){
	int i;
	for(i=0;i<SIZETABLEHASH;i++){

		Liste_flux tmp=l[i];
		l[i]=l[i]->suivant;
		free(tmp);
	}
}

