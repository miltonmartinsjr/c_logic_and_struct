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
// Montre sur l`ecran le contenu du queue
//
// INPUT :
//		  queue : semble de clients qui seront attent par une caisse
// OUTPUT :
//     
//
// Exemples :
//     {1, 2}{2, 3}{4, 4}{5, 8}{20, 67}; //semble de clients dans la queue
// *****************************************************************************
void imprimerQueue(Queue* queue[], Caisse caisses[], int cycles);
// *****************************************************************************
// obtenirQueuePlusPetite
//
// Determine le queue plus petite a partir de une sembre de queue recu par parametre
//
// INPUT :
//		  queue[] : semble de queues 
// OUTPUT :
//     
//
// Exemples :
//     {1, 2}{2, 3}{4, 4}{5, 8}{20, 67}; //semble de clients dans la queue
// *****************************************************************************
int obtenirQueuePlusPetite(Queue* queue[]);
// *****************************************************************************
// randExpo
//
// Calculer le nombre des produits pour le panier de chaque client
//
// INPUT :
//		  lambda : taille de nombre a produire 
// OUTPUT :
//     
//
// Exemples :
//     (0.1) 
// *****************************************************************************
double randExpo(double lambda);
// *****************************************************************************
// initializeCaisses
//
// intialisa chaque queue, en realisant la asignation d`une node type queue 
//
// INPUT :
//		  caisses[] : semble de caisses par la simulation 
// OUTPUT :
//     
//
// Exemples :
// *****************************************************************************
void initializeCaisses(Queue* queuesCaisses[], Caisse caisses[]);
// *****************************************************************************
// initializeCaisses
//
// intialisa chaque queue, en realisant la asignation d`une node type queue 
//
// INPUT :
//      caisses[] : semble de caisses par la simulation 
// OUTPUT :
//     
//
// Exemples :
// *****************************************************************************
int ajouteNouveauClient(Queue* queues[], int cycles);
// *****************************************************************************
// imprimeState
//
// Imprime l'state de supermarche. 
//
// INPUT :
//      nbCycles : nombre de cycle actuel
// OUTPUT :
//     
// *****************************************************************************
void imprimeState(int nbCycles);
// *****************************************************************************
// imprimeStatistiques
//
// Imprime le chifres de control du supermarche. 
//
// INPUT :
//      nbArticles : nombre de vendu
//      nbClients : nombre de clients entres
//      tempTotal : les temps total de attention
//      tempMaxium : les temps plus grande d'attention
//      nbArticlesMaxium : le nombre de articles plus grand par client
//      nbclientEnnuyeux : le nombre client sans servir 
// OUTPUT :
//     
// *****************************************************************************
void imprimeStatistiques(int nbArticles, int nbClients, int tempTotal, int tempMaxium, int nbArticleMaxium, int nbClientsEnnuyeux);
// *****************************************************************************
// servirLesCaisses
//
// Faire la attention des caisses et controle. 
//
// INPUT :
//      queues : Les queues des clients
//      caisses : les caisses de attention
//      nbArticles : nombre de vendu
//      nbClients : nombre de clients entres
//      tempTotal : les temps total de attention
//      tempMaxium : les temps plus grande d'attention
//      nbArticlesMaxium : le nombre de articles plus grand par client
//      nbclientEnnuyeux : le nombre client sans servir 
// OUTPUT :
//     
// *****************************************************************************
void servirLesCaisses(Queue* queues[], Caisse caisses[], int *nbArticles, int nbCycles, int *nbArticleMaxium, int *tempMaxium, int *tempTotal, int *nbClientsEnnuyeux);
