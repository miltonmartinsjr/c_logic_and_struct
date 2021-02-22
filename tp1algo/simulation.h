// ***************************************
// Auteur:  Milton Martins
// Travail: TP1 - Algorithmique
// Prof:    Rebecca Lapointe
// Date: 	19 Novembre 2018
//***************************************
#pragma once
// Definition variables globales
#define CAISSES 4 //Quantite de caisses
#define MIN  0 // limite inferieur
#define MAX  6 // limite superieur
#define TEMPS 1 // Quantite de temps a attend
#define CYCLES 200 // Nombre des cycles
#define CLIENT 0 // Arrive dans un client
#define TEMPSDATTENTE 30 // les temps de attend d'un client avant de retire du queue
/* States du casses */
enum STATE {FERME = 0, OUVERT, OCCUPE, DISPONIBLE};
enum BOOLEAN {FAUX = 0, VRAI};
/* Structure que decrire une caisse */
typedef struct Caisse Caisse;
struct Caisse{
  int state;
  int nombre;
  int cycle;
  int nbArticles;
};
/******************************************************************************
   Definitions des funtions   
*******************************************************************************/

// *****************************************************************************
// imprimerQueue
//
//
// INPUT :
//		  
// OUTPUT :
//     
//
// Exemples :
//    
// *****************************************************************************
void imprimerQueue(Queue* queue[], Caisse caisses[], int cycles);
// *****************************************************************************
// obtenirQueuePlusPetite
//
//
// INPUT :
//		  
// OUTPUT :
//     
//
// Exemples :
//
// *****************************************************************************
int obtenirQueuePlusPetite(Queue* queue[]);
// *****************************************************************************
// randExpo
//
//
// INPUT :
//		  
// OUTPUT :
//     
//
// *****************************************************************************
double randExpo(double lambda);
// *****************************************************************************
// initializeCaisses
//
// 
//
// INPUT :
//		   
// OUTPUT :
//     
//
// Exemples :
// *****************************************************************************
void initializeCaisses(Queue* queuesCaisses[], Caisse caisses[]);
// *****************************************************************************
// initializeCaisses
//
// 
//
// INPUT :
//      
// OUTPUT :
//     
//
// Exemples :
// *****************************************************************************
int ajouteNouveauClient(Queue* queues[], int cycles);
// *****************************************************************************
// imprimeState
//
// 
// INPUT :
//      
// OUTPUT :
//     
// *****************************************************************************
void imprimeState(int nbCycles);
// *****************************************************************************
// imprimeStatistiques
// 
//
// INPUT :
//       
// OUTPUT :
//     
// *****************************************************************************
void imprimeStatistiques(int nbArticles, int nbClients, int tempTotal, int tempMaxium, int nbArticleMaxium, int nbClientsEnnuyeux);
// *****************************************************************************
// servirLesCaisses
//
//
// INPUT :
//      
// OUTPUT :
//     
// *****************************************************************************
void servirLesCaisses(Queue* queues[], Caisse caisses[], int *nbArticles, int nbCycles, int *nbArticleMaxium, int *tempMaxium, int *tempTotal, int *nbClientsEnnuyeux);
