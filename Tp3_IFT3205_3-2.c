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
#define NAME_IMG_IN  "barbara512_Degraded"
#define NAME_IMG_OUT "image-TpIFT3205-3-2"

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
               int fft_size, float threshold) {

    static int number = 0;
    
    int i, j;
    
    float** filtered_r = fmatrix_allocate_2d(fft_size, fft_size);
    float** filtered_i = fmatrix_allocate_2d(fft_size, fft_size);
    float** filtered_mod = fmatrix_allocate_2d(fft_size, fft_size);
    
    for(i=0; i<fft_size; i++)
        for(j=0; j<fft_size; j++) {
            
            filtered_r[i][j] = img_r[offsety + i][offsetx + j];
            filtered_i[i][j] = 0;
            
        }

    FFTDD(filtered_r, filtered_i, fft_size, fft_size);

    Mod(filtered_mod, filtered_r, filtered_i, fft_size, fft_size);

    float max = fabs(filtered_r[0][0]);
    
    for(i=0; i<fft_size; i++)
        for(j=0; j<fft_size; j++) {
            if(filtered_mod[i][j] < threshold * max) {
                filtered_r[i][j] = 0;
                filtered_i[i][j] = 0;
            }
        }
    
    IFFTDD(filtered_r, filtered_i, fft_size, fft_size);

    for(i=0; i<length; i++)
        for(j=0; j<width; j++) {
            if(img_orig[i][j] == 255) {
                img_r[i][j] = filtered_r[i - offsety][j - offsetx];
            }
        }

    free_fmatrix_2d(filtered_r);
    free_fmatrix_2d(filtered_i);
    free_fmatrix_2d(filtered_mod);

    //Sauvegarde
    char name[50];

    number++;
    
    sprintf(name, "image-TpIFT3205-3-2-%d", number);
    
    //Commande systeme: VISU
    SaveImagePgm(name, img_r, length, width);
    
    char BufSystVisuImg[100];
    
    strcpy(BufSystVisuImg,NAME_VISUALISER);
    
    strcat(BufSystVisuImg, name);
    
    strcat(BufSystVisuImg,".pgm&");
    
    system(BufSystVisuImg);
}

/*------------------------------------------------*/
/* Et maintenant, notre PROGRAMME PRINCIPAL   ----*/                     
/*------------------------------------------------*/
int main(int argc,char **argv) {
    int i,j;
    int length,width;

    //Lecture Image 
    float** img = LoadImagePgm(NAME_IMG_IN,&length,&width);
    float** img_r = LoadImagePgm(NAME_IMG_IN,&length,&width);

    //Interpolation
    // 5 itérations
    iteration(img, img_r, length, width,
              0, 0, 512, 0.04);
    iteration(img, img_r, length, width,
              128, 128, 256, 0.02);
    iteration(img, img_r, length, width,
              128, 240, 256, 0.01);
    iteration(img, img_r, length, width,
              128, 168, 256, 0.005);
    iteration(img, img_r, length, width,
              128, 200, 256, 0.0025);
        
    return 0; 	 
}
