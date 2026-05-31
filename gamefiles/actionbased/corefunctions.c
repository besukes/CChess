#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>



int calcPosClique(int lower_border_limit , int upper_border_limit , int pos , int square_size){
    int c = 0;
    for(int i = lower_border_limit ; i < upper_border_limit ; i+=square_size,c++){
        if(i <= pos && pos <= i + square_size){
            return c;
        }
    }
    return (-1);
}

Coordenadas click_table_position(int mouseX , int mouseY){
    int infHorizontal = 600 , supHorizontal = 1320 ,
        infVertical = 100 , supVertical = 800;
    int tamanhoQuadrado = (supHorizontal - infHorizontal) / 8 ;
    int cx = calcPosClique(infHorizontal,supHorizontal,mouseX,tamanhoQuadrado) , 
        cy = calcPosClique(infVertical,infHorizontal,mouseY,tamanhoQuadrado);
    Coordenadas p = {.coluna = cx,.linha=cy};
    return p;
}