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
#define NAME_IMG_OUT "image-TpIFT3205-2-1b"

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/
/*------------------------------------------------*/

float matrix_valw(float** m, int j, int i, int length, int width) {

    if(i < 0 || i >= length)
        i = (i + length) % length;
    
    if(j < 0 || j >= width)
        j = (j + width) % width;

    return m[i][j];
}

void matrix_resize_billy(float** src, float** dest, int l1, int w1, int l2, int w2) {
    int x1,y1,x2,y2;
    float xp,yp;
    
    float dx, dy;
    float f_xy, f_x1y, f_xy1, f_x1y1, f_xpy, f_xpy1;

    float fact_l = l2/(float)l1, fact_w = w2/(float)w1;

    for(y2=0; y2<l2; y2++) {
        for(x2=0; x2<w2; x2++) {

            xp = x2/fact_w;
            yp = y2/fact_l;
            
            x1 = (int) xp;
            y1 = (int) yp;
                
            dx = xp - x1;
            dy = yp - y1;
            
            f_xy = matrix_valw(src, x1, y1, l1, w1);

            f_x1y = matrix_valw(src, x1 + 1, y1, l1, w1);

            f_xy1 = matrix_valw(src, x1, y1 + 1, l1, w1);

            f_x1y1 = matrix_valw(src, x1 + 1, y1 + 1, l1, w1);

            f_xpy = f_xy + dx * (f_x1y - f_xy);

            f_xpy1 = f_xy1 + dx * (f_x1y1 - f_xy1);

            dest[y2][x2] = f_xpy + dy * (f_xpy1 - f_xpy);
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
    matrix_resize_billy(orig, bigger, length, width, length*4, width*4);
 
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
