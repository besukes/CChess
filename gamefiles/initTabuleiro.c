#include "library/main.h"


void initTabRooks(PecaTabuleiro pt[32],int fst){
    int diffPosicaoRooks = 0;
    for(int i=0;i<2;i++,diffPosicaoRooks+=7){
        pt[fst + i].cor = Preta;
        pt[fst + i].tipoPiece = Pawn;
        pt[fst + i].firstTimeMoving = 1;
        pt[fst + i].linhaTabuleiro = 0;
        pt[fst + i].colunaTabuleiro = i;

        pt[fst + i + 2].cor = Preta;
        pt[fst + i + 2].tipoPiece = Pawn;
        pt[fst + i + 2].firstTimeMoving = 1;
        pt[fst + i + 2].linhaTabuleiro = 0;
        pt[fst + i + 2].colunaTabuleiro = i;
    }
}

void initTabPawns(PecaTabuleiro pt[32],int max){
    int meio = max / 2; // 8
    int i;
    for(i=0;i<meio;i++){
        pt[i].cor = Preta;
        pt[i].tipoPiece = Pawn;
        pt[i].firstTimeMoving = 1;
        pt[i].linhaTabuleiro = 1;
        pt[i].colunaTabuleiro = i;

        pt[i + meio].cor = Branca;
        pt[i + meio].tipoPiece = Pawn;
        pt[i + meio].firstTimeMoving = 1;
        pt[i + meio].linhaTabuleiro = 6;
        pt[i + meio].colunaTabuleiro = i;
    }
}

PecaTabuleiro * initTabuleiro(PecaTabuleiro pt[32]){
    initTabPawns(pt,16);
    initTabRooks(pt);
    initTabHorses(pt);
    initTabBishops(pt);
    initTabQueens(pt);
    initTabKings(pt);
}