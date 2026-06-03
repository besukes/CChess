#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>


int posTabuleiro(uint64_bit bitboard){
    if(bitboard==0) return (-1);
    return __builtin_ctzll(bitboard);
}


int calcPosClique(int lower_border_limit , int upper_border_limit , int pos , int square_size , int type){
    int c = (type) ? 0 : 7;
    for(int i = lower_border_limit ; i < upper_border_limit ; i+=square_size){
        if(i <= pos && pos < i + square_size){
            return c;
        }
        if(type) c++;
        else c--;
    }
    return (-1);
}

uint64_bit click_table_position(int mouseX , int mouseY){
    uint64_bit p = 0;
    int infHorizontal = 600 , supHorizontal = 1320 ,
        infVertical = 100 , supVertical = 800;
    int tamanhoQuadrado = (supHorizontal - infHorizontal) / 8;
    int cx = calcPosClique(infHorizontal,supHorizontal,mouseX,tamanhoQuadrado,1) , 
        cy = calcPosClique(infVertical,supVertical,mouseY,tamanhoQuadrado,0);
    if(cx!=(-1) && cy != (-1)){
        p = (1ULL<<((cy*8)+cx));
    }
    return p;
}