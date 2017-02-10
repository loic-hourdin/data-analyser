#include "liste_routeur.h"

Liste_routeur routeurs_cons (Liste_routeur l, T nvelt, routeur pa){
Liste_routeur p;
p = malloc(sizeof(struct routeur_maillon));
p->donnee = nvelt;
p->suivant=l;
p->p=pa;
return(p);
}

int routeurs_appartient(T x, Liste_routeur l){
if ( l == NULL ) return(0);
if ( x == l->donnee ) return(1);
return(routeurs_appartient(x, l->suivant));
}

Liste_routeur routeurs_add (Liste_routeur l, T e, routeur pa){
return(routeurs_cons(l,e,pa));
}
Liste_routeur routeurs_find (Liste_routeur l, T e){
	while (l!=NULL){
		if(l->donnee==e){
			//printf("find\n");
			return(l);
		}
		l=l->suivant;
	}
	return(l);
}
void routeurs_free(Liste_routeur l){
	while(l!=NULL){
		Liste_routeur tmp=l;
		fclose(l->p.f);
		l=l->suivant;
		free(tmp);
	}	
}


