#include "library/main.h"



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

AffectedPositions * initPosicoesAfetadas(int additor){
    AffectedPositions * af = malloc(sizeof(AffectedPositions)*32);
    af->refferedPiece = Pawn;
    af->cordJogo = malloc(sizeof(Coordenadas)*16);
    af->refferedPiece = Horse;
    (af+1)->cordJogo = malloc(sizeof(Coordenadas)*4);
    int l = 1 + additor , counter = 0;
    int linhaDif = (additor == 0) ? 1 : -1;
    for(int i=0;i<8;i++,counter+=2){
        Coordenadas * c = af->cordJogo + counter;
        c->linha = l;
        c->coluna = i;
        af->cordenadaPiece
        (c + 1)->linha = l + linhaDif;
        (c + 1)->coluna = i;
    }
    initPosicoesCavalos((af+1)->cordJogo,additor+linhaDif);
}

