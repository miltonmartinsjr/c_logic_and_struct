  // ****************************************************************************
  // Nom : Queue.h
  //
  // Auteur :  William Guerrero
  //
  // Date : 5 Novembre 2018
  //
  // funtions pour controle le comportament d`une queue.
  //
  // *****************************************************************************
#pragma once
/* Structure que decrire une client */
typedef struct Client Client;
struct Client{
	int cycles;
	int nbArticles;
	Client* suivant;
};
/* Structure que decrire une Queue */
typedef struct Queue Queue;
struct Queue{
    Client* premier;
    Client* dernier;
};
/******************************************************************************
   Definitions des funtions   
*******************************************************************************/

// *****************************************************************************
// initialize
//
// function que asigne la memoire pour le node queue 
//
// INPUT :
//		  
// OUTPUT :
//       queue : direction de memoire pour le premier node du queue
//
// Exemples :
// *****************************************************************************
Queue* initialize();
// *****************************************************************************
// offrirClient
//
// function que permetter ajouter une client a quelque queue
//
// INPUT :
//		 queue : id du queue a faire la inclusion de le nouveau client
//		 client : Donnes de client a ajouter a la queue 
// OUTPUT :
//       
//
// Exemples :
// *****************************************************************************
void offrirClient(Queue* queue, Client* client);
// *****************************************************************************
// obtenirTete
//
// function que permetter obtenir une client a apartir d`une queue
//
// INPUT :
//		 queue : queue d`attention des clients
//		  
// OUTPUT :
//       client : Donnes de client a effacer de queue
//
// Exemples :
// *****************************************************************************
Client* obtenirTete(Queue* queue);
// *****************************************************************************
// coupDOeilTete
//
// function que permetter obtenir une client a apartir d`une queue sans effacer le 
// donnes
//
// INPUT :
//		 queue : queue d`attention des clients
//		  
// OUTPUT :
//       client : Donnes de client a consulter de queue
//
// Exemples :
// *****************************************************************************
Client* coupDOeilTete(Queue* queue);
// *****************************************************************************
// clientParQueue
//
// function que permetter obtenir la quantite de clients par queue 
//
// INPUT :
//		 queue : queue d`attention des clients
//		  
// OUTPUT :
//       int  : quantite des clients
//
// Exemples :
// *****************************************************************************
int longueurQueue(Queue* queue);
// *****************************************************************************
// clientParQueue
//
// function que permetter obtenir la quantite de clients par queue 
//
// INPUT :
//     queue : queue d`attention des clients
//      
// OUTPUT :
//       int  : quantite des clients
//
// Exemples :
// *****************************************************************************
Client* nouveauClient(int cycle, double nbArticles);
// *****************************************************************************
// retireClient
//
// function que retirer du queue  
//
// INPUT :
//     queue : queue d`attention des clients
//     tempAttent : les temps de attent
//     cycle : le nombre de cycle de attention   
//      
// OUTPUT :
//       int  : quantite des clients retires
//
// Exemples :
// *****************************************************************************
int retireClient(Queue* queue, int tempAttent, int cycle);
