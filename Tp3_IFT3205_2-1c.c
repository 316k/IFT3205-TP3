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
#define NAME_IMG_OUT "image-TpIFT3205-2-1c"

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/
/*------------------------------------------------*/
void PreFFT_Translation(float** Matrix, int length, int width) {
    int x,y;
    for(x=0; x<length; x++)
        for(y=0; y<width; y++)
            if((x + y) % 2 == 1)
                Matrix[x][y] = -Matrix[x][y];
}

/*------------------------------------------------*/
/* Et maintenant, notre PROGRAMME PRINCIPAL   ----*/                     
/*------------------------------------------------*/
int main(int argc,char **argv) {
    int i,j;
    int length,width;
    char BufSystVisuImg[100];

    //Lecture Image 
    float** img_r    = LoadImagePgm(NAME_IMG_IN,&length,&width);
    float** img_i    = fmatrix_allocate_2d(length,width);
    float** bigger_r = fmatrix_allocate_2d(length*4,width*4);
    float** bigger_i = fmatrix_allocate_2d(length*4,width*4);

    //Interpolation
    PreFFT_Translation(img_r, length, width);
    FFTDD(img_r, img_i, length, width);

    for(i=0; i<length; i++)
        for(j=0; j<width; j++) {
            bigger_r[i + length*3/2][j + width*3/2] = img_r[i][j];
            bigger_i[i + length*3/2][j + width*3/2] = img_i[i][j];
        }

    IFFTDD(bigger_r, bigger_i, length*4, width*4);
    PreFFT_Translation(bigger_r, length*4, width*4);
    Recal(bigger_r, length*4, width*4);
 
    //Sauvegarde
    SaveImagePgm(NAME_IMG_OUT,bigger_r,length*4,width*4);

    //Commande systeme: VISU
    strcpy(BufSystVisuImg,NAME_VISUALISER);
    strcat(BufSystVisuImg,NAME_IMG_OUT);
    strcat(BufSystVisuImg,".pgm&");
    printf(" %s",BufSystVisuImg);
    system(BufSystVisuImg);    
    
    return 0; 	 
}
