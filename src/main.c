#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "donne.h"

#define        BUFSIZE      5000


int main(int argc, char *argv[])

{

    test=0;


    int i,l,c;
    int a=0;
    FILE* file = NULL;
    FILE* file2 = NULL;
    long  vread;
    char  buf[BUFSIZE];
    int   rest=0;
    int   endread = 0;
    int   stopwhile = 0;          
    long  pos = 0;
    long nbr=0;
    nbr_packet=0;
    nbr_packet_instantane=0;
    nbr_flux=0;
    nbr_routeur=0;
    nbrtreaty=0;
    nbr_wait=0;
    donne donne;
    moy_bb=new_moy_double();
    moy_timewait=new_moy_double();
    moy_timetrans=new_moy_double();

    for(i=0;i<SIZETABLEHASH;i++)packets[i]=NULL;
    packets_old=NULL;
    routeurs=NULL;
    for(i=0;i<SIZETABLEHASH;i++)fluxs[i]=NULL;
    

//pour pplot
    FILE *gnuplot = popen("gnuplot", "w");
    file_t_bb = fopen("donne/t_bb.dat", "w");
    file_nbr_packet = fopen("donne/nbr_packet.dat", "w");
    file_nbr_lost = fopen("donne/nbr_lost.dat", "w");
    file_nbr_wait = fopen("donne/nbr_wait.dat", "w");
    file_nbr_packets = fopen("donne/nbr_packets.dat", "w");

//pour les arguments
    packets_save=NULL;
    pid_read=NULL;
    fid_read=NULL;
    char etat_tmp=0;
    int val_tmp;
    char* adrdon=NULL;
    char* adrtab=NULL;
    for(i=1;i<argc;i++){
        val_tmp=atol(argv[i]);
        //printf("etat:%i\n",etat_tmp);
        if(argv[i][0]=='-'){
            if(!strcmp(argv[i],"-pid"))etat_tmp=1;
            else if(!strcmp(argv[i],"-fid"))etat_tmp=2;
            else if(!strcmp(argv[i],"-f"))etat_tmp=3;
            else if(!strcmp(argv[i],"-tab"))etat_tmp=4;
            else {
                printf("::erreur:: bad argument (%s) \n argument valid: -f (fichier de donné) -tab (fichier avec tableau débit) -pid 'pid1' 'pid2' ...  -fid 'fid1' 'fid2' ...\n pid ou fid = 0 interdit\n",argv[i]);
                return 0;
            }
        }
        else{
            if(etat_tmp==0){
                printf("::erreur:: bad argument (%s)\n argument valid: -f (fichier de donné) -tab (fichier avec tableau débit) -pid 'pid1' 'pid2' ...  -fid 'fid1' 'fid2' ...\n pid ou fid = 0 interdit\n",argv[i]);
                return 0;
            }
            else if(etat_tmp==1){
                pid_read=cons(pid_read,val_tmp);
            }
            else if(etat_tmp==2){
                fid_read=cons(fid_read,val_tmp);
            }
            else if(etat_tmp==3){
                adrdon=argv[i];
            }
            else if(etat_tmp==4){
                adrtab=argv[i];
            }

        }
    }
    if(adrdon==NULL){
        printf("::erreur:: -f (fichier de donné) non donné\n");
        return 0;
    }

    if(adrtab!=NULL){

        




        if (!(file = fopen(adrtab,"r")))
        {
            perror("::erreur:: imposible de lire le fichier");
            return 0;
        }
        l=0;
        c=1;
         do
        {
            vread = fread(buf+rest, 1, sizeof(buf)-rest, file);
            if (vread<1)     
            {

                endread = 1;
                vread  = 0;
                break;
            }     
            //buf[BUFSIZE-1] = 0;   
            pos=0;
            i=rest;
            stopwhile=0;
            while(i!=vread+rest && stopwhile==0){
                if(buf[i]=='\0'){
                    stopwhile=1;
                    break;
                }
                else{
                    if(buf[i]=='\n'){
                        l++;
                        pos=i+1;                     
                    }
                    if(l==1 && buf[i]=='\t'){
                        c++;
                    }

                }
                i++;
            }
            
            rest = BUFSIZE-pos;
            if (rest<1) rest=0;     

            if (pos!=0 && rest!=0)
            memmove(buf, buf+pos, rest); 
        } while(!endread);


        rest=0;
        endread = 0;
        stopwhile = 0;          
        pos = 0;
        nbr=0;
        fseek(file, 0, SEEK_SET);

        debit=malloc(l*sizeof(int*));
        for(i=0;i<l;i++){
            debit[i]=malloc(c*sizeof(int));
        }

        l=0;
        c=0;

         do
        {
            vread = fread(buf+rest, 1, sizeof(buf)-rest, file);
            if (vread<1)     
            {

                endread = 1;
                vread  = 0;
                break;
            }       
            pos=0;
            i=rest;
            stopwhile=0;
            while(i!=vread+rest && stopwhile==0){
                if(buf[i]=='\0'){
                    stopwhile=1;
                    break;
                }
                else{
                    if(buf[i]=='\n'){
                        buf[i]='\0';
                        debit[l][c]=atoi((char*)buf+pos);
                        l++;
                        pos=i+1;
                        c=0;                   
                    }
                    if(buf[i]=='\t'){
                        buf[i]='\0';
                        debit[l][c]=atoi((char*)buf+pos);
                        pos=i+1;
                        c++;
                    }

                }
                i++;
            }
            
            rest = BUFSIZE-pos;
            if (rest<1) rest=0;     

            if (pos!=0 && rest!=0)
            memmove(buf, buf+pos, rest); 
        } while(!endread);



       fclose(file);
    }
    else debit==NULL;


    // Open source file
    if (!(file2 = fopen(adrdon,"r")))
    {
        perror("::erreur:: imposible de lire le fichier");
        return 0;
    }


    rest=0;
    endread = 0;
    stopwhile = 0;          
    pos = 0;
    nbr=0;

    do
    {
        vread = fread(buf+rest, 1, sizeof(buf)-rest, file2);
        if (vread<1)     
        {

            endread = 1;
            vread  = 0;
            break;
        }     
 
        pos=0;
        i=rest;
        stopwhile=0;
        while(i!=vread+rest && stopwhile==0){
            if(buf[i]=='\0'){
                stopwhile=1;
            }
            else{
                if(buf[i]=='\n'){
                    sscanf(buf+pos,"%lf %d %d %d %d %d N%d N%d N%d", &donne.t, &donne.code, &donne.pid, &donne.fid, &donne.tos, &donne.bif, &donne.s, &donne.d, &donne.pos);
                    pos=i+1;
                    nbr++;
                    donne_maj(donne); 
                }
            }
            i++;
        }
        if(nbr%10000==0){
            printf("nbr de ligne lue:%ld\n",nbr);
            a=0;
            for(i=0;i<SIZETABLEHASH;i++){
                 packets_old=packets[i];
                while(packets_old!=NULL){
                    a++;
                    packets_old=packets_old->suivant;
                }
            }
            
            printf("nbr de packet actif:%i\n",a);
    }
        rest = BUFSIZE-pos;
        if (rest<1) rest=0;     

        if (pos!=0 && rest!=0)
        memmove(buf, buf+pos, rest); 
    } while(!endread);

   fclose(file2);
  

printf("\n----donnée global-----------------------------------------------------------------------------------------------------------------------------\n");
   printf("nbr routeur:%ld\n",nbr_routeur);
   printf("nbr flux:%ld\n",nbr_flux);
   printf("nbr paquets:%ld\n",nbr_packet);
   printf("nbr perdu:%ld\n",nbrlost);
   printf("taux de perte:%f\n",(float)nbrlost/nbr_packet);
   printf("moy_bb: %f ic=(%f,%f) ec=%f\n",moyenne_double_moy(moy_bb),moyenne_double_ic_moin(moy_bb),moyenne_double_ic_plus(moy_bb), moyenne_double_ec(moy_bb));
   printf("moy_timewait: %f ic=(%f,%f) ec=%f\n",moyenne_double_moy(moy_timewait),moyenne_double_ic_moin(moy_timewait),moyenne_double_ic_plus(moy_timewait), moyenne_double_ec(moy_timewait));
   printf("moy_timetrans: %f ic=(%f,%f) ec=%f\n",moyenne_double_moy(moy_timetrans),moyenne_double_ic_moin(moy_timetrans),moyenne_double_ic_plus(moy_timetrans), moyenne_double_ec(moy_timetrans));


   Liste_routeur r=routeurs;
    printf("\n----routeurs------------------------------------------------------------------------------------------------------------\n");
   printf("n°noeud\tmoy temps d'att(intervale de confiance)\ttaux de perte\tnbr de perte\tnbr départ\tnbr arrivé\tnbr émis\tnbr reçus\n");
   while(r!=NULL){
        printf("%i\t%f(%f,%f)\t\t%f\t%i\t\t%i\t\t%i\t\t%i\t\t%i\n",r->p.num,moyenne_double_moy(r->p.moy_t_wait),moyenne_double_ic_moin(r->p.moy_t_wait),moyenne_double_ic_plus(r->p.moy_t_wait),(float)r->p.nb_lost/(r->p.nb_start+r->p.nb_recieved),r->p.nb_lost,r->p.nb_start,r->p.nb_end,r->p.nb_send,r->p.nb_recieved);
        r=r->suivant;
   }
   Liste_flux f;
   int h_fid;
   if(fid_read!=NULL)printf("\n----fluxs---------------------------------------------------------------------------------------------------------------\n");
   if(fid_read!=NULL)printf("fid\tnbr émis\tnbr reçus\tnbr lost\ttemps debut\ttemps fin\ttemps de vie\tmoy temps d'acheminement(ic)\n");
   while(fid_read!=NULL){
        h_fid=hash(fid_read->donnee);
        f=fluxs_find(fluxs[h_fid],fid_read->donnee);
        if(f==NULL){
            printf("fid=%ld non existant\n",fid_read->donnee );
        }
        else{
            printf("%i\t%i\t\t%i\t\t%i\t\t%f\t%f\t%f\t%f(%f,%f)\n",f->p.fid,f->p.nb_send,f->p.nb_recieved,f->p.nb_lost,f->p.t_start,f->p.t_start+f->p.t_life,f->p.t_life,moyenne_double_moy(f->p.moy_t_acheminement),moyenne_double_ic_moin(f->p.moy_t_acheminement),moyenne_double_ic_plus(f->p.moy_t_acheminement));
        }
        fid_read=fid_read->suivant;
   }
   if(packets_save!=NULL)printf("----Paquet-------------------------------------------------------------------------------------------------------------\n");
   if(packets_save!=NULL)printf("pid\tsource\tdest\tt envoie\tt fin \t\ttaille\tmoy temps d'att\t\t\tmoy temps de transmition\tnoeud parcourue\n");
   while(packets_save!=NULL){
        printf("%i\t%i\t%i\t%f\t%f\t%i\t%f(%f,%f)\t%f(%f,%f)\t%ld",packets_save->p.pid,packets_save->p.s,packets_save->p.d,packets_save->p.t_start,packets_save->p.t_end,packets_save->p.taille,moyenne_double_moy(packets_save->p.moy_t_wait),moyenne_double_ic_moin(packets_save->p.moy_t_wait),moyenne_double_ic_plus(packets_save->p.moy_t_wait),moyenne_double_moy(packets_save->p.moy_t_trans),moyenne_double_ic_moin(packets_save->p.moy_t_trans),moyenne_double_ic_plus(packets_save->p.moy_t_trans),packets_save->p.routeur->donnee);
        packets_save->p.routeur=packets_save->p.routeur->suivant;
        while(packets_save->p.routeur!=NULL){
            printf("-%ld",packets_save->p.routeur->donnee);
            packets_save->p.routeur=packets_save->p.routeur->suivant;
        }
        printf("\n");
        packets_save=packets_save->suivant;
    }

fprintf(gnuplot, "reset\nset title \"nbr_de_paquet\"\nplot 'donne/nbr_packets.dat' with lines\nset terminal png\nset output \"graph/nbr_de_paquet.png\"\nreplot\n");
fprintf(gnuplot, "reset\nset title \"temps_bout_a_bout\"\nplot 'donne/t_bb.dat' with lines\nset terminal png\nset output \"graph/temps_bout_a_bout.png\"\nreplot\n");
fprintf(gnuplot, "reset\nset title \"nbr perdu\"\nplot 'donne/nbr_lost.dat' with lines\nset terminal png\nset output \"graph/nbr_perdu.png\"\nreplot\n");
fprintf(gnuplot, "reset\nset title \"nbr of paquets in the network\"\nplot 'donne/nbr_packet.dat' with lines\nset terminal png\nset output \"graph/nbr_paquet_dans_le_réseau.png\"\nreplot\n");
fprintf(gnuplot, "reset\nset title \"nbr_de_paquet_dans_les_files_d'attentes\"\nplot 'donne/nbr_wait.dat' with lines\nset terminal png\nset output \"graph/nbr_de_paquet_dans_les_files_d'att.png\"\nreplot\n");

r=routeurs;
if(r!=NULL){
    fprintf(gnuplot, "reset\nset title \"nbr of paquets in wait in node\"\nplot 'donne/noeud/N%i.dat' with lines",r->p.num);
    r=r->suivant;
}
while(r!=NULL){
    fprintf(gnuplot, ", 'donne/noeud/N%i.dat' with lines",r->p.num);
    r=r->suivant;
}   
fprintf(gnuplot, "\nset terminal png\nset output \"graph/node_wait.png\"\nreplot\n");

fclose(file_t_bb);
fclose(file_nbr_packet);
fclose(file_nbr_lost);
fclose(file_nbr_wait);
fluxs_free(fluxs);
Packets_free(packets);
routeurs_free(routeurs);

fflush(gnuplot);
    return EXIT_SUCCESS;


}