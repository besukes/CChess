#include "library/main.h"
#include <stdlib.h>

void initPosicoesCavalos(Coordenadas * af1, int line){
    af1->coluna = 0;
    af1->linha = line;
    (af1 + 1) ->coluna = 2;
    (af1 + 1) ->linha = line;
    (af1 + 2) ->coluna = 5;
    (af1 + 2) ->linha = line;
    (af1 + 3) ->coluna = 7;
    (af1 + 3) ->linha = line;
}

void initAffectedPositionsHorses(AffectedPositions * af , int start,int additor){
    Coordenadas arr[4] = { {.linha=0,.coluna=1} , {.linha=0,.coluna=6} , 
                           {.linha=7,.coluna=1} , {.linha=7,.coluna=6} 
                        };
    int linhaDif = (additor == 0) ? 1 : -1 , pr = 1;
    for(int i=0;i<4;i++){
        pr=1;
        (af+start+i)->cordenadaPiece.linha = arr[i].linha;
        (af+start+i)->cordenadaPiece.coluna = arr[i].coluna;
        (af+start+i)->refferedPiece = Horse;
        (af+start+i)->cordJogo = malloc(sizeof(Coordenadas)*2);
        Coordenadas * c  = (af+start+i)->cordJogo;
        for(int j=0;j<2;j++,pr=-1){
            (c+j)->coluna = arr[i].coluna + pr;
            (c+j)->linha = arr[i].linha + linhaDif*2;
        }
    }
}

void initAffectedPositionsPawn(AffectedPositions * af , int start,int lim ,int additor){
    int l = 1 + additor , counter = 0;
    int linhaDif = (additor == 0) ? 1 : -1;
    for(int i=start;i<lim;i++,counter=0){
        (af+i)->cordenadaPiece.linha = l;
        (af+i)->cordenadaPiece.coluna = i;
        (af+i)->refferedPiece =  Pawn;
        (af+i)->cordJogo = malloc(sizeof(Coordenadas)*2);
        Coordenadas * c  = (af+i)->cordJogo;
        for(int j=0;j<2;j++,counter++){
            (c+j)->coluna = i;
            (c+j)->linha = l + linhaDif*j;
        }
    }
}

AffectedPositions * initPosicoesAfetadas(int additor){
    AffectedPositions * af = malloc(sizeof(AffectedPositions)*32);
    initAffectedPositionsPawn(af,0,8,additor);
    initAffectedPositionsHorses(af,8,additor);
    return af;
}

