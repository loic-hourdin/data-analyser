#include "liste.h"

Liste cons (Liste l, T nvelt){
Liste p;
p = malloc(sizeof(struct maillon));
p->donnee = nvelt;
p->suivant=l;
return(p);
}

int appartient(T x, Liste l){
if ( l == NULL ) return(0);
if ( x == l->donnee ) return(1);
return(appartient(x, l->suivant));
}

Liste add (Liste l, T e){
return(cons(l,e));
}

void affiche (Liste l){
	do{
		printf("%ld ",l->donnee);
		l=l->suivant;
	}while (l!=NULL);
	printf("\n");
}

int position (Liste l, T e){
	int i=0;
	do{
		if (l->donnee==e){
			return i;
		}
		l=l->suivant;
		i++;
	}while (l!=NULL);
	return -1;
}

int nombre (Liste l, T e){
	int i=0;
	do{
		if (l->donnee==e){
			i++;
		}
		l=l->suivant;
		
	}while (l!=NULL);
	return i;}

int sommeite(Liste l){
	int s=0;
	while (l!=NULL){
		s=s+l->donnee;
		l=l->suivant;
	}
	return s;}

void free_liste(Liste l){
	while(l!=NULL){
	Liste tmp=l;
	l=l->suivant;
	free(tmp);
	}
}


int sommerec(Liste l){
	if (l==NULL){
		return(0);
	}
	else{return(l->donnee+sommerec(l->suivant));
	}}
//non finie
