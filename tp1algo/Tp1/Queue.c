  // ****************************************************************************
  // Nom : Queue.c
  //
  // Auteur :  William Guerrero
  //
  // Date : 5 Novembre 2018
  //
  // funtions pour controle le comportament d`une queue.
  //
  // *****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"


Queue* initialize(){
	Queue *queue = (struct Queue *) malloc(sizeof(Queue));
  if (queue != NULL){
    queue->premier = NULL;
    queue->dernier = NULL;
  }
  return queue;
}

void offrirClient(Queue* queue, Client* nouveau){
    if (!queue->premier){
        queue->premier = nouveau;
        queue->dernier = nouveau;             
    }
    else
    {
        queue->dernier->suivant = nouveau;
        queue->dernier = nouveau;
    }  
}

Client* obtenirTete(Queue* queue){
    if(queue->premier){
        Client* client = queue->premier; 
        queue->premier = queue->premier->suivant;
        return client;
    }
    return queue->premier;
}


Client* coupDOeilTete(Queue* queue){
    return queue->premier;
}

int longueurQueue(Queue* queue){
    Client* cliente = queue->premier; 
    int quantite = 0;
    while(cliente != NULL){
        cliente = cliente->suivant;
        quantite++; 
    }
    return quantite;
}

Client* nouveauClient(int cycle, double nbArticles){
  Client* nouveau = (struct Client *) malloc(sizeof(Client));
  if (nouveau != NULL) {
    nouveau->cycle = cycle;
    nouveau->nbArticles = nbArticles;
    nouveau->suivant = NULL;
  }
  return nouveau;  
}


int retireClient(Queue* queue, int tempAttent, int cycle){
  Client* precedent = queue->premier;
  int quantite = 0;
  while (precedent->suivant != NULL) {
    Client* nouveau = precedent->suivant;
    if (nouveau != NULL){
      if ((cycle - nouveau->cycle) >= tempAttent){ 
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
