#include "library/main.h"




void initPieces(PecaTabuleiro pt[32],int index,int tipo,casas_board pos,int difPos){
    if(tipo==0){
        pt[index].bitboard_position |= (1ULL << pos);
        pt[index].bitboard_position |= (1ULL << (pos + difPos));
    }
    else{
        pt[index].bitboard_position |= (1ULL << (56 + pos));
        pt[index].bitboard_position |= (1ULL << (56 + pos + difPos));
    }
}


void initTabPawns(PecaTabuleiro pt[16],int tipo){
    if(tipo==0){
        pt[0].bitboard_position |= (1ULL << A2);
        pt[0].bitboard_position |= (1ULL << B2);
        pt[0].bitboard_position |= (1ULL << C2);
        pt[0].bitboard_position |= (1ULL << D2);
        pt[0].bitboard_position |= (1ULL << E2);
        pt[0].bitboard_position |= (1ULL << F2);
        pt[0].bitboard_position |= (1ULL << G2);
        pt[0].bitboard_position |= (1ULL << H2);
    }
    else{
        pt[0].bitboard_position |= (1ULL << A7);
        pt[0].bitboard_position |= (1ULL << B7);
        pt[0].bitboard_position |= (1ULL << C7);
        pt[0].bitboard_position |= (1ULL << D7);
        pt[0].bitboard_position |= (1ULL << E7);
        pt[0].bitboard_position |= (1ULL << F7);
        pt[0].bitboard_position |= (1ULL << G7);
        pt[0].bitboard_position |= (1ULL << H7);
    }
}

PecaTabuleiro * initTabuleiro(PecaTabuleiro pt[16], int additor){
    initTabPawns(pt,additor);
    initPieces(pt,1,additor,A1,7); //rook
    initPieces(pt,2,additor,B1,5); //horse
    initPieces(pt,3,additor,C1,3); //bishop
    initPieces(pt,4,additor,D1,0); //queen
    initPieces(pt,5,additor,E1,0); //king
}

void init_other_bitboards(EstadoJogo * es){
    es->bitboard_brancas = 0;
    es->bitboard_pretas = 0;
    for(int i = 0 ; i < 16 ; i++){
        es->bitboard_brancas |= es->tabuleirojogo[0][i].bitboard_position;
        es->bitboard_pretas |= es->tabuleirojogo[1][i].bitboard_position;
    }
    es->bitboard_todas_pieces = es->bitboard_brancas | es->bitboard_pretas;
}