#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>




int minimum(int n1,int n2){
    return ((n1<n2)? n1 : n2);
}



Pieces comparePiece(EstadoJogo estado , CorPiece cor , uint64_bit posclique){
    int i;
    for(i=0;i<6;i++){
        if(estado.tabuleirojogo[cor][i] & posclique){
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
    for(int i = lower_border_limit ; i <= upper_border_limit ; i+=square_size){
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
    int infHorizontal = 200 , supHorizontal = 1075 ,
        infVertical = 38 , supVertical = 913;
    int tamanhoQuadrado = 125;
    int cx = calcPosClique(infHorizontal,supHorizontal,mouseX,tamanhoQuadrado,1) , 
        cy = calcPosClique(infVertical,supVertical,mouseY,tamanhoQuadrado,0);
    if(cx!=(-1) && cy != (-1)){
        p = (1ULL<<((cy*8)+cx));
    }
    return p;
}



void addHeadLinkedList(PecasComidasLL * list , Pieces piece_comida , uint64_bit pos_piece , CorPiece cor){
    PecasComidasLL novo = malloc(sizeof(struct PecasComidas));
    novo->cor_piece = cor;
    novo->pos_de_piece = pos_piece;
    novo->tipo_piece = piece_comida;
    novo->prox = *list;
    *list = novo;
}


void removeHeadLinkedList(PecasComidasLL * list){
    PecasComidasLL u = *list;
    *list = (*list)->prox;
    free(u);
}


void getColunasAH(uint64_bit * colunaA , uint64_bit * colunaH){
    *colunaA = 0ULL;
    *colunaH = 0ULL;
    for(int i=0;i<8;i++){
        *colunaA |= (1ULL<< (8*i));
        *colunaH |= (1ULL<< (8*i + 7));
    }
}





void king_line_dependant_moves(uint64_bit * atk ,uint64_bit (*func)(uint64_bit,int),uint64_bit pos_rei , uint64_bit colunaA , uint64_bit colunaH){
    uint64_bit coluna1,coluna2;
    if(func==&shiftl){
        coluna1 = colunaA;
        coluna2 = colunaH;
    }else{
        coluna1 = colunaH;
        coluna2 = colunaA;
    }
    *atk |= func(pos_rei,8);
    *atk |= func(pos_rei&~coluna1,7);
    *atk |= func(pos_rei&~coluna2,9);
}