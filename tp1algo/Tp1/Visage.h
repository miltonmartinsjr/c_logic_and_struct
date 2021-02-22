  // ****************************************************************************
  // Nom : visage.c
  //
  // Auteur :  William Guerrero
  //
  // Date : 5 novembre 2018
  //
  // funtions pour faire l'ecran d'application.
  //
  // *****************************************************************************

#pragma once
/* Parameters generales */
/* Taille d'ecran */
#define  HORIZONTALE  80 // Nombre de colones
#define  VERTICALE  25 // Nombre de ranges
/* Coleurs utilisee dans l'ecran */
enum COLEURS  {ROUGE=0, VERD, BLEU, JEUNE, BLANC};
// *****************************************************************************
// largeurTitle
//
// Calcule le largeur d'un chaine des characteres
//
// INPUT :
//     title : chaine des characteres.
//
// OUTPUT :
//     le nombre de characteres du chaine.
//
// Exemples :
//     largeurTitle("Turn") = 4;
//     largeurTitle("Test") = 4;
// *****************************************************************************
int largeurTitle(char *title);
// *****************************************************************************
// gotoxy
//
// Position de cursor sur l'ecran
//
// INPUT :
//     x : position horizontale.
//     y : position verticale.
//
// OUTPUT :
//
// Exemples :
//     gotoxy(5,5);
// *****************************************************************************
void gotoxy(int x,int y);
// *****************************************************************************
// ecriteColor
//
// Ecrite un chaine de characteres dans un coleur, dans un position
//
// INPUT :
//     sortie : chaine de characteres.
//     x : position horizontale.
//     y : position verticale.
//     coleur : coleur a utiliser.
//
// OUTPUT :
//
// Exemples :
//     ecriteColor("Ton Pointage", 5, 5, ROUGE);
// *****************************************************************************
void ecriteColor(char *sortie, int x, int y, int coleur);
// *****************************************************************************
// imprimeCadre
//
// Cree un cadre a partir de les valeurs que recu comme parameters
//
// INPUT :
//     x : position horizontale initial.
//     y : position verticale initial.
//     x : position horizontale finale.
//     y : position verticale finale.
//     title : title du cadre.
//
// OUTPUT :
//
// Exemples :
//     imprimeCadre(1, 1, 80, 24, "Yahtzee");
// *****************************************************************************
void imprimeCadre(int x, int y, int x1, int y1, char *title);