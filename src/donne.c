#include "donne.h"

void donne_maj(donne donne){
	nbrtreaty++;
	Liste_packet pp=NULL;
	int tmp;
	int h=hash(donne.pid);
	int h_fid=hash(donne.fid);
	packets_old=Packets_find(packets[h],donne.pid);
	if(packets_old!=NULL){
		pp=packets_old->suivant;
	}
	else {
		if(packets[h]==NULL)pp=NULL;
		else pp=packets[h];
	}
	
	Liste_flux ff=fluxs_find(fluxs[h_fid],donne.fid);

	Liste_routeur rr;
	if(donne.code==2){
		rr=routeurs_find(routeurs,pp->p.pos);
	}
	else{
		rr=routeurs_find(routeurs,donne.pos);
	}



	if(rr==NULL){
		routeur routeur;
		routeur.num=donne.pos;
    	routeur.nb_lost=0;
    	routeur.moy_t_wait=new_moy_double();
    	routeur.nb_recieved=0;
    	routeur.nb_send=0;
    	routeur.nb_start=0;
    	routeur.nb_end=0;
    	routeur.nb_wait=0;
    	char* ctmp;
		sprintf(ctmp,"donne/noeud/N%i.dat",donne.pos);
		routeur.f = fopen(ctmp,"w");
		if (!routeur.f)    {
        perror("::erreur:: imposible de lire le fichier");
    	}
    	routeurs=routeurs_cons(routeurs,donne.pos,routeur);
    	rr=routeurs;
    	nbr_routeur++;

	}
	if(ff==NULL){
			flux flux;
			flux.fid=donne.fid;
		    flux.nb_send=0;
		    flux.nb_recieved=0;
		    flux.nb_lost=0;
		    flux.t_start=donne.t;
		    flux.t_life=0;
		    flux.moy_d_send=new_moy_double();
		    flux.moy_t_recieved=new_moy_double();
		    flux.moy_t_acheminement=new_moy_double();
		    fluxs[h_fid]=fluxs_cons (fluxs[h_fid], donne.fid,flux);
		    ff=fluxs[h_fid];
		    nbr_flux++;
	}
	if(pp==NULL){
			packet packet;
			packet.pid=donne.pid;
			packet.s=donne.s;
			packet.d=donne.d;
			packet.pos=donne.pos;
			packet.t_start=donne.t;
			packet.t_start_wait=donne.t;
			packet.t_start_trans=donne.t;
			packet.t_wait=0;
			packet.routeur=cons(NULL,donne.s);
			packet.taille=0;
			packet.moy_t_trans=new_moy_double();
			packet.moy_t_wait=new_moy_double();

			packets[h]=Packets_cons (packets[h], donne.pid,packet);
			pp=packets[h];
			nbr_packet++;
			nbr_packet_instantane++;
			fprintf(file_nbr_packet, "%f %ld\n", donne.t, nbr_packet_instantane);
			fprintf(file_nbr_packets, "%f %ld\n", donne.t, nbr_packet);
	}



	if(donne.code==0){
		rr->p.nb_start++;
		ff->p.nb_send=ff->p.nb_send+1;
		nbr_wait++;
		fprintf(file_nbr_wait, "%f %ld\n", donne.t, nbr_wait);
		rr->p.nb_wait++;
		fprintf(rr->p.f,"%f %i\n", donne.t, rr->p.nb_wait);
	}
	
	if(donne.code==1){
		pp->p.t_start_wait=donne.t;
		
		rr->p.nb_recieved++;
		pp->p.routeur=cons(pp->p.routeur,donne.pos);
		if(debit!=NULL)
		pp->p.taille=(debit[(pp->p.s)-1][(pp->p.d)-1])*(donne.t-pp->p.t_start_trans)+(debit[(pp->p.d)-1][(pp->p.s)-1])*(donne.t-pp->p.t_start_trans);
		pp->p.moy_t_trans=moyenne_double_maj(pp->p.moy_t_trans,donne.t-pp->p.t_start_trans);
		//ff->p.moy_t_acheminement=moyenne_double_maj(ff->p.moy_t_acheminement,donne.t-pp->p.t_start_trans);
		moy_timetrans=moyenne_double_maj(moy_timetrans,donne.t-pp->p.t_start_trans);
		nbr_wait++;
		fprintf(file_nbr_wait, "%f %ld\n", donne.t, nbr_wait);
		rr->p.nb_wait++;
		fprintf(rr->p.f,"%f %i\n", donne.t, rr->p.nb_wait);
		pp->p.pos=donne.pos;




	}
	if(donne.code==2){
		pp->p.t_wait=pp->p.t_wait+donne.t-pp->p.t_start_wait;
		pp->p.moy_t_wait=moyenne_double_maj(pp->p.moy_t_wait,donne.t-pp->p.t_start_wait);
		rr->p.moy_t_wait=moyenne_double_maj(rr->p.moy_t_wait,donne.t-pp->p.t_start_wait);
		moy_timewait=moyenne_double_maj(moy_timewait,donne.t-pp->p.t_start_wait);
		rr->p.nb_send++;
		
		pp->p.t_start_trans=donne.t;
		nbr_wait--;
		fprintf(file_nbr_wait, "%f %ld\n", donne.t, nbr_wait);
		rr->p.nb_wait--;
		fprintf(rr->p.f,"%f %i\n", donne.t, rr->p.nb_wait);
	}



	if(donne.code==3){
			//printf("%i\n",donne.pid);
			if(donne.t-pp->p.t_start<=0)printf("erreur sous\n");
			moy_bb=moyenne_double_maj(moy_bb,donne.t-pp->p.t_start);
			fprintf(file_t_bb, "%f %f\n", donne.t,donne.t-pp->p.t_start);
			//printf("%f\n",pp->p.t_start );
			if(pp!=NULL){
				if(packets_old==NULL){
					packets[h]=pp->suivant;
					tmp=0;
						Liste tmp_read=pid_read;
						while(tmp_read!=NULL){
					        if(tmp_read->donnee==donne.pid){
					        	tmp=1;
					        	pp->p.t_end=donne.t;
					        	pp->p.destroy=0;
					        }
					        tmp_read=tmp_read->suivant;
					    }
					    if(tmp){
					    	if(packets_save==NULL){
				    		packets_save=pp;
				    	}
					    	else {
					    		pp->suivant=packets_save;
					    		packets_save=pp;
					    	}
					    }
					    else{	
					    	free(pp);
						}		
					nbr_packet_instantane--;
					fprintf(file_nbr_packet, "%f %ld\n", donne.t, nbr_packet_instantane);
				}
				else{
					if(packets_old->suivant!=NULL){
						packets_old->suivant=pp->suivant;
						tmp=0;
						Liste tmp_read=pid_read;
						while(tmp_read!=NULL){
					        if(tmp_read->donnee==donne.pid){
					        	tmp=1;
					        	pp->p.t_end=donne.t;
					        	pp->p.destroy=1;
					        }
					        tmp_read=tmp_read->suivant;
					    }
					    if(tmp){
					    	if(packets_save==NULL){
				    		packets_save=pp;
				    	}
					    	else {
					    		pp->suivant=packets_save;
					    		packets_save=pp;

					    	}
					    }
					    else{	
					    	free(pp);
						}		
						nbr_packet_instantane--;
						fprintf(file_nbr_packet, "%f %ld\n", donne.t, nbr_packet_instantane);
					}
					else{
						printf("erreur code 4 pour packet non existant\n");

					}
				}
			}
			else{
				printf("erreur code 4 pour packets[h] vide\n");
			}
			
			//printf("mm\n");
			nbrreceived++;
			rr->p.nb_end++;
			ff->p.nb_recieved++;
			ff->p.t_life=donne.t-ff->p.t_start;
			ff->p.moy_t_acheminement=moyenne_double_maj(ff->p.moy_t_acheminement,donne.t-pp->p.t_start_trans);
			pp->p.moy_t_trans=moyenne_double_maj(pp->p.moy_t_trans,donne.t-pp->p.t_start_trans);
			moy_timetrans=moyenne_double_maj(moy_timetrans,donne.t-pp->p.t_start_trans);
			nbr_wait--;
			fprintf(file_nbr_wait, "%f %ld\n", donne.t, nbr_wait);
			rr->p.nb_wait--;
			fprintf(rr->p.f,"%f %i\n", donne.t, rr->p.nb_wait);

		}
	if(donne.code==4){
			if(pp!=NULL){
				if(packets_old==NULL){
					packets[h]=pp->suivant;
					tmp=0;
					Liste tmp_read=pid_read;
					while(tmp_read!=NULL){
				        if(tmp_read->donnee==donne.pid)tmp=1;
				        tmp_read=tmp_read->suivant;
				    }
				    if(tmp){
				    	if(packets_save==NULL){
				    		packets_save=pp;
				    	}
				    	else {
				    		pp->suivant=packets_save;
				    		packets_save=pp;

				    	}
				    }
				    else{	
				    	free(pp);
					}		
					nbr_packet_instantane--;
					fprintf(file_nbr_packet, "%f %ld\n", donne.t, nbr_packet_instantane);
				}
				else{
					if(packets_old->suivant!=NULL){
						
						packets_old->suivant=pp->suivant;
						tmp=0;
						Liste tmp_read=pid_read;
						while(tmp_read!=NULL){
					        if(tmp_read->donnee==donne.pid)tmp=1;
					        tmp_read=tmp_read->suivant;
					    }
					    if(tmp){
					    	if(packets_save==NULL){
				    		packets_save=pp;
				    	}
					    	else {
					    		pp->suivant=packets_save;
					    		packets_save=pp;
					    	}
					    }
					    else{	
					    	free(pp);
						}						
						nbr_packet_instantane--;
						fprintf(file_nbr_packet, "%f %ld\n", donne.t, nbr_packet_instantane);
					}
					else{
						printf("erreur code 4 pour packet non existant\n");

					}
				}
			}
			else{
				printf("erreur code 4 pour packets[h] vide\n");
			}
			nbrlost++;
			fprintf(file_nbr_lost, "%f %ld\n", donne.t, nbrlost);
			rr->p.nb_lost++;
			ff->p.nb_lost++;
			ff->p.t_life=donne.t-ff->p.t_start;
			nbr_wait--;
			fprintf(file_nbr_wait, "%f %ld\n", donne.t, nbr_wait);
			rr->p.nb_wait--;
			fprintf(rr->p.f,"%f %i\n", donne.t, rr->p.nb_wait);
                       // if(donne.pos==donne.s)printf("LOLO%i\n",pp->p.pid);

	}

}


int hash(long a){
	return(a%SIZETABLEHASH);
}
