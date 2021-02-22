  // ****************************************************************************
  // Nom : QueueCashier.h
  //
  // Auteur :  William Guerrero
  //
  // Date : 5 Novembre 2018
  //
  // funtions pour faire la simulations dans l`attention de caisses.
  //
  // *****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "Queue.h"
#include "QueueCashier.h"
#include "Visage.h"


double randExpo(double lambda){
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
    imprimeCadre(1, 1, 80, 24, "");
    imprimeCadre(2, 2, 79, 4, "SuperMarche Maxi");
    gotoxy(3, 3); 
    printf("Instant %d \t\t\t\t\t Moniteur Siege de Laval" , cycles);
    for (int i = 0; i < CAISSES; i++){    
        gotoxy(7, 7 + (i * 2));
        printf("Caisse (%d) : [" , caisses[i].nombre );
        if (caisses[i].state == OUVERT || (longueurQueue(queue[i]) == 0 && cycles >= CYCLES)){
            ecriteColor("Ferme", 21, 7 + (i * 2), ROUGE);
            ecriteColor("]", 26, 7 + (i * 2), BLANC);
        }
        if (caisses[i].state == DISPONIBLE && longueurQueue(queue[i]) == 0 && cycles <= CYCLES){
            ecriteColor("Disponible", 21, 7 + (i * 2), VERD);
            ecriteColor("]", 31, 7 + (i * 2), BLANC);
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
                if ((cycles - client->cycle) >= (TEMPSDATTENTE - CAISSES)){
                    printf("\033[1;31m");
                    printf("{*%d,#%d}", client->cycle, client->nbArticles); 
                    printf("\033[0m");    
                }else{ 
                    printf("{*%d,#%d}", client->cycle, client->nbArticles);
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
                caisses[i].cycle = client->cycle;
                caisses[i].nombre = i + 1;
                caisses[i].state = OCCUPE;         
            }
        }        
        //Valider l`existance de client dans la queue
        if (caisses[i].state == OCCUPE){
            if ( caisses[i].nbArticles > 0 ){
                caisses[i].nbArticles--;
                (*nbArticles)++;
                (*nbClientsEnnuyeux) += retireClient(queues[i], TEMPSDATTENTE, nbCycles);
            }
            else{
                Client *client = obtenirTete(queues[i]);
                if ( client ){
                    //Calculer la quantite plus grande d`articles par panier
                    if(client->nbArticles > (*nbArticleMaxium))
                        (*nbArticleMaxium) = client->nbArticles;
                    //Calculer le temps maxium de attend  
                    if((nbCycles - client->cycle) > (*tempMaxium))
                        (*tempMaxium) = nbCycles - client->cycle;   
                    //liberer la memoire
                    free( client );
                }
                caisses[i].state = DISPONIBLE;
            }
            (*tempTotal)++;
        }       
    }
}

void imprimeStatistiques(int nbArticles, int nbClients, int tempTotal, int tempMaxium, int nbArticleMaxium, int nbClientsEnnuyeux){
    gotoxy(5, 18);
    printf("Nombre de clients entre  : %d        Nombre d'articles vendus : %d", nbClients, nbArticles);
    gotoxy(5, 19);
    printf("Temps d'attente total    : %d        Temps d'attente moyen    : %d", tempTotal, (nbClients > 0) ? tempTotal / nbClients : 0);    
    gotoxy(5, 20);
    printf("Temps d'attente maxium   : %d        Nombre d'articles maxium : %d", tempMaxium, nbArticleMaxium);
    gotoxy(5, 21);
    printf("Clients sans servir      : %d        Nombre d'articles moyen  : %d", nbClientsEnnuyeux, (nbClients > 0) ? nbArticles / nbClients : 0);
    gotoxy(5, 22);
    printf("Temps de attente heureux : %d",  TEMPSDATTENTE);
}

void imprimeState(int nbCycles){
    if (nbCycles <= CYCLES)
        ecriteColor("SuperMarche Ouvert. :-P", 30, 23, VERD);
    else     
        ecriteColor("SuperMarche Ferme. :-(", 30, 23, ROUGE);
}

int main(){
    Queue* queuesCaisses[CAISSES];
    Caisse caisses[CAISSES];
    //Variables pour determine les resultats et moyens
    int nbCycles = 1; //nombre de cycles executes
    int nbClients = 0; //nombre de clients recus
    int nbArticles = 0; // nombre d`articles vendus
    int tempTotal = 0;// temps totale de service
    int nbArticleMaxium = 0; // le plus grand nombre de articles vendu
    int tempMaxium = 0; // le plus gran temp de attent
    int nbClientsEnnuyeux = 0; //Nombre clients pas de attention

    srand(time(NULL));
    //Faire l`initialisation les queues et Initialise les caisses
    initializeCaisses(queuesCaisses, caisses);
    //Faire le boucle jusqu'a le parameter defini     
    while (nbCycles <= CYCLES || quantiteCaissesOccupes(caisses)){
        //Pour le exercise le nombres pairs seront considere comment clients
        if ( cestClient() && nbCycles <= CYCLES){
        	//Ajouter le neuveau client a la Queue
            if ( ajouteNouveauClient(queuesCaisses, nbCycles) )
                nbClients++;
            else
                nbClientsEnnuyeux++;
        }
        //Faire l`attention des caisses
        servirLesCaisses(queuesCaisses, caisses, &nbArticles, nbCycles, &nbArticleMaxium, &tempMaxium, &tempTotal, &nbClientsEnnuyeux);
        //Imprimer le cadre des resultats
        imprimerQueue(queuesCaisses, caisses, nbCycles);
        //Imprimer sommaires et les moyens
        imprimeStatistiques(nbArticles, nbClients, tempTotal, tempMaxium, nbArticleMaxium, nbClientsEnnuyeux);
        //Imprime State du supermarche
        imprimeState(nbCycles);
        //Attent 
        sleep(TEMPS);
        nbCycles++;
    }
    gotoxy(1,25);
    printf("Fin du simulation...\n");
    return 0;
}   