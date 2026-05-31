#include "library/main.h"




void checkPositions(PecaTabuleiro piece , EstadoJogo jogo){
    switch(piece.tipoPiece){
        case Pawn :

        break;
        case Rook :

        break;
        case Horse :

        break;
        case Bishop :
        
        break;
        case Queen :

        break;
        case King :

        break;
    }
}

void currentAffectedPositions(EstadoJogo estado){
    PecaTabuleiro b[16] = estado.tabuleiroJogoBrancas ,
                  p[16] = estado.tabuleiroJogoPretas;
    for(int i=0;i<16;i++){
        if(p[i].linhaTabuleiro != (-1)){
            checkPositions(p[i],estado);
        }
        if(b[i].linhaTabuleiro != (-1)){
            checkPositions(b[i],estado);
        }
    }
}