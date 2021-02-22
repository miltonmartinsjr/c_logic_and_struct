// ***************************************
// Auteur:  Milton Martins
// Travail: TP1 - Algorithmique
// Prof:    Rebecca Lapointe
// Date: 	19 Novembre 2018
//***************************************

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "queue.h"
#include "simulation.h"



double randExpo(double lambda)
{
    double u = rand() / (RAND_MAX + 1.0);
    return -log(1 - u) / lambda;
}

void initializeCaisses(Queue* queuesCaisses[], Caisse caisses[]){
    for (int i =0; i < CAISSES; i++){
        queuesCaisses[i] = initialize();
        if ( queuesCaisses[i] ){
            caisses[i].state = OUVERT;
            caisses[i].nbArticles = 0;
            caisses[i].nombre = 0;
            caisses[i].cycle = 0;
        }
    }
}

int cestClient(){
    int estClient = rand() % MAX + MIN;
    if ( estClient == CLIENT)
        return VRAI;

    return FAUX;
}


int obtenirQueuePlusPetite(Queue* queue[]){
    int taille = longueurQueue(queue[0]);
    int nbQueue = 0;
    for (int i = 1; i < CAISSES; i++){
        int largueur = longueurQueue(queue[i]);
        if (taille > largueur){
            nbQueue = i;
            taille = largueur;
        }
    }
    return nbQueue;
}


int quantiteCaissesOccupes(Caisse caisses[]){
    int quantite = 0;
    for (int i = 0; i < CAISSES; i++)
        if (caisses[i].state == OCCUPE)
            quantite++;

    return quantite;    
}

void imprimerQueue(Queue* queue[], Caisse caisses[], int cycles){
    system("clear");
    printf("DOLARAMA CENTREVILLE");
    printf("Instant %d \n Monitoring..." , cycles);
    for (int i = 0; i < CAISSES; i++){    
        printf("Caisse (%d) : [" , caisses[i].nombre );
        if (caisses[i].state == OUVERT || (longueurQueue(queue[i]) == 0 && cycles >= CYCLES)){
            printf("Ferme");
        }
        if (caisses[i].state == DISPONIBLE && longueurQueue(queue[i]) == 0 && cycles <= CYCLES){
            printf("Allez Vitte");
        }

        Client* client = queue[i]->premier;
        //Valide si il y a client dans la caisse 
        if (caisses[i].state == OCCUPE){
            printf("{*%d,#%d}", caisses[i].cycle, caisses[i].nbArticles);
            client = queue[i]->premier->suivant;
        }
        //Imprime les queue si il y a un autres clients 
        if ( client ){
            //Imprimer le contenu du Queue    
            while(client != NULL){
                //Valide si le client est moleste o pas
               if ((cycles - client->cycles) >= (TEMPSDATTENTE - CAISSES)){
                    printf("\033[1;31m");
                    printf("{*%d,#%d}", client->cycles, client->nbArticles); 
                    printf("\033[0m");    
                }else{ 
                    printf("{*%d,#%d}", client->cycles, client->nbArticles);
                } 
                client = client->suivant; 
            }
        }
        if (caisses[i].state == OCCUPE)
            printf("]");
    }        
}

int ajouteNouveauClient(Queue* queues[], int cycles){
    Client* client = nouveauClient(cycles, randExpo(0.1) + 1);
    if ( client ){
        int plusPetite = obtenirQueuePlusPetite(queues);
        offrirClient(queues[plusPetite], client);
        return VRAI;
    }
    return FAUX;
}

void servirLesCaisses(Queue* queues[], Caisse caisses[], int *nbArticles, int nbCycles, int *nbArticleMaxium, int *tempMaxium, int *tempTotal, int *nbClientsEnnuyeux){
    for (int i = 0; i < CAISSES; i++){
        if (caisses[i].state == DISPONIBLE || caisses[i].state == OUVERT){    
            Client* client = coupDOeilTete(queues[i]);
            if ( client ){
                caisses[i].nbArticles = client->nbArticles;
                caisses[i].cycle = client->cycles;
                caisses[i].nombre = i + 1;
                caisses[i].state = OCCUPE;         
            }
        }        
        
        if (caisses[i].state == OCCUPE){
            if ( caisses[i].nbArticles > 0 ){
                caisses[i].nbArticles--;
                (*nbArticles)++;
                (*nbClientsEnnuyeux) += retireClient(queues[i], TEMPSDATTENTE, nbCycles);
            }
            else{
                Client *client = obtenirTete(queues[i]);
                if ( client ){
                    
                    if(client->nbArticles > (*nbArticleMaxium))
                        (*nbArticleMaxium) = client->nbArticles;
                     
        /* */            if((nbCycles - client->cycles) > (*tempMaxium))
                        (*tempMaxium) = nbCycles - client->cycles;   
                    
                    free( client );
                }
                caisses[i].state = DISPONIBLE;
            }
            (*tempTotal)++;
        }       
    }
}

void imprimeStatistiques(int nbArticles, int nbClients, int tempTotal, int tempMaxium, int nbArticleMaxium, int nbClientsEnnuyeux){
   
    printf("Nombre de clients entre  : %d        Nombre d'articles vendus : %d", nbClients, nbArticles);
    
    printf("Temps d'attente total    : %d        Temps d'attente moyen    : %d", tempTotal, (nbClients > 0) ? tempTotal / nbClients : 0);    
  
    printf("Temps d'attente maxium   : %d        Nombre d'articles maxium : %d", tempMaxium, nbArticleMaxium);
    
    printf("Clients sans servir      : %d        Nombre d'articles moyen  : %d", nbClientsEnnuyeux, (nbClients > 0) ? nbArticles / nbClients : 0);
    
    printf("Temps de attente heureux : %d",  TEMPSDATTENTE);
}

void imprimeState(int nbCycles){
    if (nbCycles <= CYCLES)
        printf(" DOLARAMA Ouvert");
    else     
        printf("DOLARAMA Ferme");
}

int main(){
    Queue* queuesCaisses[CAISSES];
    Caisse caisses[CAISSES];

    int nbCycles = 1; 
    int nbClients = 0; 
    int nbArticles = 0; 
    int tempTotal = 0;
    int nbArticleMaxium = 0; 
    int tempMaxium = 0; 
    int nbClientsEnnuyeux = 0; 

    srand(time(NULL));
    initializeCaisses(queuesCaisses, caisses);   
    while (nbCycles <= CYCLES || quantiteCaissesOccupes(caisses)){
        if ( cestClient() && nbCycles <= CYCLES){
            if ( ajouteNouveauClient(queuesCaisses, nbCycles) )
                nbClients++;
            else
                nbClientsEnnuyeux++;
        }
        servirLesCaisses(queuesCaisses, caisses, &nbArticles, nbCycles, &nbArticleMaxium, &tempMaxium, &tempTotal, &nbClientsEnnuyeux);
        imprimerQueue(queuesCaisses, caisses, nbCycles);
        imprimeStatistiques(nbArticles, nbClients, tempTotal, tempMaxium, nbArticleMaxium, nbClientsEnnuyeux);
        imprimeState(nbCycles);
        sleep(TEMPS);
        nbCycles++;
    }
    printf("C'est fini!\n");
    return 0;
}   