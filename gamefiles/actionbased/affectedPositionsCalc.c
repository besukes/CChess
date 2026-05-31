#include "library/main.h"




void checkPositions(PecaTabuleiro piece , EstadoJogo jogo , CorPiece cor){
    switch(piece.tipoPiece){
        case Pawn :
            checkPawnPositions(piece,jogo,cor);
        break;
        case Rook :
            checkRookPositions(piece,jogo,cor);
        break;
        case Horse :
            checkHorsePositions(piece,jogo,cor);
        break;
        case Bishop :
            checkBishopPositions(piece,jogo,cor);
        break;
        case Queen :
            checkQueenPositions(piece,jogo,cor);
        break;
        case King :
            checkKingPositions(piece,jogo,cor);
        break;
    }
}

void currentAffectedPositions(EstadoJogo estado){
    PecaTabuleiro b[16] = estado.tabuleiroJogoBrancas ,
                  p[16] = estado.tabuleiroJogoPretas;
    for(int i=0;i<16;i++){
        if(p[i].linhaTabuleiro != (-1)){
            checkPositions(p[i],estado,Preta);
        }
        if(b[i].linhaTabuleiro != (-1)){
            checkPositions(b[i],estado,Branca);
        }
    }
}