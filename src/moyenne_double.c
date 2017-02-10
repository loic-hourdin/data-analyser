#include "moyenne_double.h"

moyenne_double new_moy_double(){
	moyenne_double m;
	m.a=0;
    m.q=0;
    m.k=0;
    return(m);
}


moyenne_double moyenne_double_maj(moyenne_double moy, double x){
	moy.k++;
	double old_a=moy.a;
	if(moy.k==1){
		moy.a=x;
		moy.q=0;
		return(moy);
	}
	moy.a=moy.a+((x-moy.a)/moy.k);
	moy.q=moy.q+((x-old_a)*(x-moy.a));
	return(moy);
}

double moyenne_double_ec(moyenne_double moy){
	return(sqrt(moy.q/(moy.k)));
}

double moyenne_double_moy(moyenne_double moy){
	return(moy.a);
}

void moyenne_double_ic(moyenne_double moy, double* ic0, double* ic1){
	*ic0=moy.a-2*(moyenne_double_ec(moy)/sqrt(moy.k));
	*ic1=moy.a+2*(moyenne_double_ec(moy)/sqrt(moy.k));
}

double moyenne_double_ic_plus(moyenne_double moy){
	return(moy.a+(2*(moyenne_double_ec(moy)/sqrt((float)moy.k))));
}
double moyenne_double_ic_moin(moyenne_double moy){
	return(moy.a-(2*(moyenne_double_ec(moy)/sqrt((float)moy.k))));
}
