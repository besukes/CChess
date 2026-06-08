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


int pawnFirstRank(uint64_bit pos,CorPiece cor){
    int postab = __builtin_ctzll(pos);
    if(cor==brancas){
        return(8 <= postab && postab < 16);
    }
    else{
        return( 48 <= postab && postab < 56);
    }
}


void addHeadLinkedList(PecasComidasLL * list , Pieces piece_comida , uint64_bit pos_piece , CorPiece cor){
    PecasComidasLL novo = malloc(sizeof(struct PecasComidas));
    novo->cor_piece = cor;
    novo->pos_de_piece = pos_piece;
    novo->tipo_piece = piece_comida;
    novo->prox = *list;
    *list = novo;
}

void getColunasAH(uint64_bit * colunaA , uint64_bit * colunaH){
    for(int i=0;i<8;i++){
        *colunaA |= (1ULL<< (8*i));
        *colunaH |= (1ULL<< (8*i + 7));
    }
}



int is_open_path(uint64_bit bitboard_todas_pieces,uint64_bit path , uint64_bit extraPositions){
    uint64_bit relevant_path = path & ~extraPositions;
    return ( (bitboard_todas_pieces & relevant_path )== 0);
}




int is_castelling_king(uint64_bit pos_piece , GameStruct * game , CorPiece cor){
    uint64_t destino_short = (cor == brancas) ? (1ULL << 6 | 1ULL<<7)  : (1ULL << 62 | 1ULL<<63),
             destino_long  = (cor == brancas) ? (1ULL << 2 | 1ULL <<1 | 1ULL)  : (1ULL << 58 | 1ULL << 57 | 1ULL << 56);
    Boolean castelShort = (destino_short != 0) && 
                is_open_path(game->estadoJogo.bitboard_todas_pieces,destino_short,game->estadoJogo.tabuleirojogo[cor][Rook]),
            castelLong = (destino_long != 0) && 
                is_open_path(game->estadoJogo.bitboard_todas_pieces,destino_long,game->estadoJogo.tabuleirojogo[cor][Rook]);
    return (  ( castelShort && game->estadoJogo.canCastle[cor][Short]) || (castelLong && game->estadoJogo.canCastle[cor][Long]) );
}

uint64_bit initQuadrado(void){
    uint64_bit quadrado = 0;
    quadrado|= (1ULL << A8);quadrado|= (1ULL << B8);quadrado|= (1ULL << C8);quadrado|= (1ULL << D8);quadrado|= (1ULL << E8);quadrado|= (1ULL << F8);
                                        quadrado|= (1ULL << G8);quadrado|= (1ULL << H8);
    quadrado|= (1ULL << A7);                                                                                                quadrado|= (1ULL << H7); 
    quadrado|= (1ULL << A6);                                                                                                quadrado|= (1ULL << H6); 
    quadrado|= (1ULL << A5);                                                                                                quadrado|= (1ULL << H5); 
    quadrado|= (1ULL << A4);                                                                                                quadrado|= (1ULL << H4);                                  
    quadrado|= (1ULL << A3);                                                                                                quadrado|= (1ULL << H3); 
    quadrado|= (1ULL << A2);                                                                                                quadrado|= (1ULL << H2); 
    quadrado|= (1ULL << A1);quadrado|= (1ULL << B1);quadrado|= (1ULL << C1);quadrado|= (1ULL << D1);quadrado|= (1ULL << E1);quadrado|= (1ULL << F1);
                                        quadrado|= (1ULL << G1);quadrado|= (1ULL << H1);
    return quadrado;
}