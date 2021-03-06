/*------------------------------------------------------*/
/* Prog    : Tp3_IFT3205-2-2.c                          */
/* Auteur  : Guillaume Riou, Nicolas Hurtubise          */
/* Date    : --/--/2010                                 */
/* version :                                            */ 
/* langage : C                                          */
/* labo    : DIRO                                       */
/*------------------------------------------------------*/

/*------------------------------------------------*/
/* FICHIERS INCLUS -------------------------------*/
/*------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "FonctionDemo3.h"

/*------------------------------------------------*/
/* DEFINITIONS -----------------------------------*/   
/*------------------------------------------------*/
#define NAME_VISUALISER "display "
#define NAME_IMG_IN  "lena128"
#define NAME_IMG_OUT "lena512_InterpolPPV"

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/   
/*------------------------------------------------*/


/*------------------------------------------------*/
/* Et maintenant, notre PROGRAMME PRINCIPAL   ----*/                     
/*------------------------------------------------*/
int main(int argc,char **argv) {
    int i,j;
    int length,width;
    char BufSystVisuImg[100];

    //Lecture Image 
    float** orig   = LoadImagePgm(NAME_IMG_IN,&length,&width);
    float** bigger = fmatrix_allocate_2d(length*4,width*4);

    //Interpolation 
    //......
 
    //Sauvegarde
    SaveImagePgm(NAME_IMG_OUT,MatriceImg1,length,width);

    //Commande systeme: VISU
    strcpy(BufSystVisuImg,NAME_VISUALISER);
    strcat(BufSystVisuImg,NAME_IMG_OUT);
    strcat(BufSystVisuImg,".pgm&");
    printf(" %s",BufSystVisuImg);
    system(BufSystVisuImg);
    
    
    return 0; 	 
}
