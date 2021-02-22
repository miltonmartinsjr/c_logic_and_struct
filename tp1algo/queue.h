// ***************************************
// Auteur:  Milton Martins
// Travail: TP1 - Algorithmique
// Prof:    Rebecca Lapointe
// Date: 	19 Novembre 2018
//***************************************

#pragma once

// Structure pour les clients.
typedef struct Client Client;
struct Client{ 
	int nbArticles;
	int cycles;
	Client* suivant;
};

// Structure pour la file.
typedef struct Queue Queue;
struct Queue{ 
	Client* premier;
	Client* dernier;
};
//*******************************************************
// 			FUNCITONS
//*******************************************************
Client* creerClient(int instantArrive, int nbArticles);
//*******************************************************
//creerClient
//
//Function que un client pour la queue.
//
//INPUT:
//
//OUTPUT: 

//********************************************************
Queue* creerQueue();
//*******************************************************
//creerClient
//
//Function que un client pour la queue.
//
//INPUT:
//
//OUTPUT: 

//********************************************************
void offrirClient(Queue* queue, Client* client);
//*******************************************************
//creerClient
//
//Function que un client pour la queue.
//
//INPUT:
//
//OUTPUT: 

//********************************************************
Client* coupDOeilTete(Queue* queue);
//*******************************************************
//creerClient
//
//Function que un client pour la queue.
//
//INPUT:
//
//OUTPUT: 

//********************************************************
Client* retirerTete(Queue* queue);
//*******************************************************
//creerClient
//
//Function que un client pour la queue.
//
//INPUT:
//
//OUTPUT: 

//********************************************************
int longueurQueue(Queue* queue);
//*******************************************************
//creerClient
//
//Function que un client pour la queue.
//
//INPUT:
//
//OUTPUT: 

//************************************************************
int suprimerClient(Queue* queue, int tempAtend, int instant);
//************************************************************
//creerClient
//
//Function que un client pour la queue.
//
//INPUT:
//
//OUTPUT: 

//********************************************************
