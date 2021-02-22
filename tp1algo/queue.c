// ***************************************
// Auteur:  Milton Martins
// Travail: TP1 - Algorithmique
// Prof:    Rebecca Lapointe
// Date: 	19 Novembre 2018
//***************************************

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Creer le client
Client* creerClient(int instantArrive, int nbArticles)
{
	Client* client = (Client*)malloc(sizeof(Client));
	client->suivant = NULL;
	client->instant = instantArrive;
	client->nbArticles = nbArticles;
	return client;

}

// Creer le file
Queue* creerQueue()
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->premier = NULL;
    queue->dernier = NULL;	
    return queue;
}


// Ajouté le client a la fin de queue.
void offrirClient(Queue* queue, Client* client)
{
	if (queue != NULL){
		if(queue->premier == NULL){
			queue->premier = client;
			queue->dernier = client;
		}
		else{
            queue->dernier->suivant = client;
            queue->dernier = client; 
		}
	}
}


// Retourne le premier client dans la queue.
// Si la queue est vide, NULL est retourne.
Client* coupDOeilTete(Queue* queue)
{
	return queue->premier;
}


// Retire et retourne le premier client dans la queue.
// Si la queue est vide, NULL est retourne.
Client* retirerTete(Queue* queue)
{
 	if(queue == NULL)
   return NULL;
	if(queue->premier){
		Client* client = queue->premier;
		queue->premier = queue->premier->suivant;
		return client;
	}
	return queue->premier;
}


// Retourne le nombre de clients dans la queue.
int longueurQueue(Queue* queue)
{
	Client* client = queue->premier;
	int compteur = 0;
	while(client !=NULL){
		compteur++;
		client = client->suivant;
	}
   return compteur;
}


// Retirer le client
int suprimerClient(Queue* queue, int tempAtend, int instant)
{
	Client* precedent = queue->premier;
  	int quantite = 0;
  	while (precedent->suivant != NULL) {
    Client* nouveau = precedent->suivant;
    if (nouveau != NULL){
      if ((instant - nouveau->instant) >= tempAtend){ 
          precedent->suivant = nouveau->suivant;
          free(nouveau);
          quantite++;
      }
      else{
          precedent = nouveau;
      } 
    }  
  }
  return quantite;
}  

