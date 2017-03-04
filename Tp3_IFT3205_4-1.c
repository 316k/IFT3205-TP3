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
#define NAME_IMG_IN  "ParcMontRoyal"
#define NAME_IMG_OUT "image-TpIFT3205-4-1"

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

void iteration(float** img_orig, float** img_r,
               int length, int width,
               int offsetx, int offsety,
               int dft_size_x, int dft_size_y, float threshold) {

    static int number = 0;
    
    int i, j;
    
    float** filtered_r = fmatrix_allocate_2d(dft_size_y, dft_size_x);
    float** filtered_i = fmatrix_allocate_2d(dft_size_y, dft_size_x);
    float** filtered_mod = fmatrix_allocate_2d(dft_size_y, dft_size_x);
    
    for(i=0; i<dft_size_y; i++)
        for(j=0; j<dft_size_x; j++) {
            
            filtered_r[i][j] = img_r[offsety + i][offsetx + j];
            filtered_i[i][j] = 0;
            
        }

    DFT(filtered_r, filtered_i, dft_size_y, dft_size_x);

    Mod(filtered_mod, filtered_r, filtered_i, dft_size_y, dft_size_x);

    float max = fabs(filtered_r[0][0]);
    
    for(i=0; i<dft_size_y; i++)
        for(j=0; j<dft_size_x; j++) {
            if(filtered_mod[i][j] < threshold * max) {
                filtered_r[i][j] = 0;
                filtered_i[i][j] = 0;
            }
        }
    
    IDFT(filtered_r, filtered_i, dft_size_y, dft_size_x);

    for(i=offsety; i < offsety + dft_size_y; i++)
        for(j=offsetx; j < offsetx + dft_size_x; j++) {
            if(img_orig[i][j] == 255) {
                img_r[i][j] = filtered_r[i - offsety][j - offsetx];
            }
        }

    Mult(img_r, 1, length, width);
    free_fmatrix_2d(filtered_r);
    free_fmatrix_2d(filtered_i);
    free_fmatrix_2d(filtered_mod);

    //Sauvegarde
    char name[50];

    number++;
    
    sprintf(name, "image-TpIFT3205-4-1-%d", number);
    
    //Commande systeme: VISU
    /* SaveImagePgm(name, img_r, length, width); */
    
    /* char BufSystVisuImg[100]; */
    
    /* strcpy(BufSystVisuImg,NAME_VISUALISER); */
    
    /* strcat(BufSystVisuImg, name); */
    
    /* strcat(BufSystVisuImg,".pgm&"); */
    
    /* system(BufSystVisuImg); */
}

/*------------------------------------------------*/
/* Et maintenant, notre PROGRAMME PRINCIPAL   ----*/                     
/*------------------------------------------------*/
int main(int argc,char **argv) {
    int i, j, k;
    int length, width;
    int extra_height = 40;

    //Lecture Image 
    float** orig = LoadImagePgm(NAME_IMG_IN,&length,&width);
    float** img = fmatrix_allocate_2d(length + extra_height, width);
    float** img_r = fmatrix_allocate_2d(length + extra_height, width);

    for(i=0; i<length; i++)
        for(j=0; j<width; j++) {
            img_r[i + extra_height][j] = orig[i][j];
        }

    for(j=0; j<width; j++) {
        float moyenne = 0;

        for(i=0; i<extra_height; i++) {
            moyenne += orig[i][j];
        }

        moyenne /= extra_height;

        for(i=0; i<extra_height; i++) {
            img_r[i][j] = moyenne;
            img[i][j] = 255;
        }
    }
    
    //Interpolation
    
    for(i=0; i<width; i++) {
        float focken = 0.4;
        
        for(j=0; j<10; j++) {
            iteration(img, img_r, length + extra_height, width,
                      i * 4, 0, fmin(8, width - i), 90, focken);
            
            focken /= 2;
        }
    }
    
    SaveImagePgm(NAME_IMG_OUT, img_r, length + extra_height, width);
    
    return 0; 	 
}
