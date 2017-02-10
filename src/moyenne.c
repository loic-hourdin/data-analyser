#include "moyenne.h"

moyenne new_moy(){
	moyenne m;
	m.a=0;
    m.q=0;
    m.k=0;
    return(m);
}


moyenne moyenne_maj(moyenne moy, long x){
	moy.k++;
	long old_a=moy.a;
	if(moy.k==1){
		moy.a=x;
		moy.q=0;
		return(moy);
	}
	moy.a=moy.a+(x-moy.a)/moy.k;
	moy.q=moy.q+(x-old_a)*(x-moy.a);
	return(moy);
}

long moyenne_ec(moyenne moy){
	return(moy.q/(moy.k-1));
}

long moyenne_moy(moyenne moy){
	return(moy.a);
}

void moyenne_ic(moyenne moy, long* ic0, long* ic1){
	*ic0=moy.a-2*(moyenne_ec(moy)/sqrt(moy.k));
	*ic1=moy.a+2*(moyenne_ec(moy)/sqrt(moy.k));
}
