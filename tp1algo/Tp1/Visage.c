// ****************************************************************************
// Nom : visage.c
//
// Auteur : William Guerrero
//
// Date : 5 novembre 2018
//
// funtions pour faire l'ecran d'application..
//
// *****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "Visage.h"


int largeurTitle(char *title){
  int largueur = 0;
  for(int i = 0; title[i] != '\0'; i++ )
    largueur++;

  return largueur;
}

void gotoxy(int x,int y)
{
  printf("%c[%d;%df",0x1B,y,x);
}


void ecriteColor(char *sortie, int x, int y, int coleur){
  switch(coleur){
  case ROUGE:
    printf("\033[1;31m\n"); 
    break;
  case VERD:
    printf("\033[1;32m\n");
    break;
  case BLEU:
    printf("\033[1;34m\n");
    break;
  case JEUNE:
    printf("\033[1;33m\n");
    break;  
  default:
    printf("\033[0m\n");
    break;
  }

  gotoxy(x, y);
  printf("%s", sortie);
  printf("\033[0m\n");
}

void imprimeCadre(int x, int y, int x1, int y1, char *title){
  int a = largeurTitle(title);
  gotoxy(x,y);
  printf("\u2554");
  for(int i = x + 1; i <= x1 - 1; i++ ){
    gotoxy(i,y);
    printf("\u2550");
    gotoxy(i,y1);
    printf("\u2550");
  }
  gotoxy(x1,y);  
  printf("\u2557");
  for(int i = y + 1; i <= y1 - 1; i++ ){
    gotoxy(x,i);
    printf("\u2551");
    gotoxy(x1,i);
    printf("\u2551");
  }
  gotoxy(x,y1);  
  printf("\u255A");
  gotoxy(x1,y1);  
  printf("\u255D");


  if (largeurTitle(title) >= 1){
    ecriteColor(title, x + (((x1 - x) / 2) - (largeurTitle(title) / 2)), y, BLEU);
  }
}
