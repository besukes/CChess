#include "library/main.h"



void initTabQueensKing(PecaTabuleiro pt[32], int fst , int pos , Pieces peca , int linha ,CorPiece cor){
    for(int i=0;i<2;i++){
        pt[fst + i].cor = cor;
        pt[fst + i].tipoPiece = peca;
        pt[fst + i].firstTimeMoving = 1;
        pt[fst + i].linhaTabuleiro = linha;
        pt[fst + i].colunaTabuleiro = pos;
    }
}

void initTabRooksHorsesBishops(PecaTabuleiro pt[32],int fst , int pos1 , int pos2, Pieces peca,int linha,CorPiece cor){
    for(int i=0;i<2;i++){
        pt[fst + i].cor = cor;
        pt[fst + i].tipoPiece = peca;
        pt[fst + i].firstTimeMoving = 1;
        pt[fst + i].linhaTabuleiro = linha;
        pt[fst + i].colunaTabuleiro = pos1;
        pos1=pos2;
    }
}


void initTabPawns(PecaTabuleiro pt[32],int max,int ad , CorPiece cor){
    int i;
    for(i=0;i<max;i++){
        pt[i].cor = cor;
        pt[i].tipoPiece = Pawn;
        pt[i].firstTimeMoving = 1;
        pt[i].linhaTabuleiro = 1 + ad;
        pt[i].colunaTabuleiro = i;
    }
}

PecaTabuleiro * initTabuleiro(PecaTabuleiro pt[16], int additor){
    CorPiece cor;
    int position;
    if(additor==0){
        cor=Preta;position=0;
    }
    else{
        cor=Branca;position=7;
    }
    initTabPawns(pt,8,additor,cor);
    initTabRooksHorsesBishops(pt,8,0,7,Rook,position,cor);
    initTabRooksHorsesBishops(pt,10,1,6,Horse,position,cor);
    initTabRooksHorsesBishops(pt,12,2,5,Bishop,position,cor);
    initTabQueensKing(pt,14,3,Queen,position,cor);
    initTabQueensKing(pt,15,4,King,position,cor);
}