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
#define NAME_IMG_OUT "image-TpIFT3205-2-1a"

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/   
/*------------------------------------------------*/
void matrix_resize_ppv(float** src, float** dest, int l1, int w1, int l2, int w2) {
    int x1,y1,x2,y2;
    float xp,yp;

    float fact_l = l2/(float)l1, fact_w = w2/(float)w1;

    for(y2=0; y2<l2; y2++) {
        for(x2=0; x2<w2; x2++) {
            
            x1 = floor(x2/fact_w);
            y1 = floor(y2/fact_l);

            dest[y2][x2] = src[y1][x1];
        }
    }
}


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
    matrix_resize_ppv(orig, bigger, length, width, length*4, width*4);
 
    //Sauvegarde
    SaveImagePgm(NAME_IMG_OUT,bigger,length*4,width*4);

    //Commande systeme: VISU
    strcpy(BufSystVisuImg,NAME_VISUALISER);
    strcat(BufSystVisuImg,NAME_IMG_OUT);
    strcat(BufSystVisuImg,".pgm&");
    printf(" %s",BufSystVisuImg);
    system(BufSystVisuImg);    
    
    return 0; 	 
}
