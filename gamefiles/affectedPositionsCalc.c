#include "library/main.h"



void currentAffectedPositions(EstadoJogo estado){
    PecaTabuleiro p[32] = estado.tabuleiroJogo;
    for(int i=0;i<32;i++){
        if(p[i].linhaTabuleiro != (-1)){
            switch(p->tipoPiece){
                case Pawn :
                    calculatePawnPositions(p[i],estado);
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
                default:break;
            }
        }
    }
}