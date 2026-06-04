#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

int minimum(int n1,int n2){
    return ((n1<n2)? n1 : n2);
}

Pieces comparePiece(EstadoJogo * estado , CorPiece cor , uint64_bit posclique){
    uint64_bit bool = 0;
    int i;
    for(i=0;i<6;i++){
        if(estado->tabuleirojogo[cor][i].bitboard_position & posclique){
            return((Pieces)i);
        }
    }
    return Empty;
}



int dentroDoBotao(int mx , int my , int inf_x , int sup_x , int inf_y , int sup_y){
    return ( (inf_x<=mx && mx<=sup_x) && (inf_y <= my && my<=sup_y));
}


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