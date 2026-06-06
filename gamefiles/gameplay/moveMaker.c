#include "library/main.h"
#include <stdio.h>


void undoMove(GameStruct * game , uint64_bit click){

}

void efetuaJogada(uint64_bit * selected_piece , uint64_bit * todas_pieces , uint64_bit original_coords , uint64_bit click , uint64_bit * mesmacor){
    *mesmacor = ( ( (*mesmacor) & (~original_coords) ) | click);
    *selected_piece = ( ( (*selected_piece) & (~original_coords) ) | click);
    *todas_pieces = ( ( (*todas_pieces) & (~original_coords)) | click);
}

void fetch_change_board(GameStruct * game,uint64_bit click,uint64_bit * mesmaCor , uint64_bit * corOposta){
    CorPiece turno = game->turnoJogador;
    CorPiece cor_oposta = (turno == brancas) ? pretas : brancas;
    int i;
    Pieces piece_comida , selected = game->pieceSelecionada;
    for(i=0;i<6 && !(game->estadoJogo.tabuleirojogo[cor_oposta][i] & click);i++);
    if(i==6) printf("[ERROR] In function fetch_change_board\n");
    else{
        piece_comida = (Pieces)i;
        addHeadLinkedList(&(game->lastmoves),piece_comida,click,cor_oposta);
        game->estadoJogo.tabuleirojogo[cor_oposta][i] &= ~(click);
        *corOposta &= ~click;
        efetuaJogada(&(game->estadoJogo.tabuleirojogo[turno][selected]),
                     &(game->estadoJogo.bitboard_todas_pieces),game->pieceCoords,
                     click,mesmaCor
                    );
    }
}


void atualizaJogada(GameStruct * game , uint64_bit click){
    CorPiece turno = game->turnoJogador;
    uint64_bit * bitboard_cor_oposta , * bitboard_cor_turno;
        if(turno==brancas){
            bitboard_cor_oposta = &(game->estadoJogo.bitboard_pretas);
            bitboard_cor_turno = &(game->estadoJogo.bitboard_brancas);
        }
        else{
            bitboard_cor_oposta = &(game->estadoJogo.bitboard_brancas);
            bitboard_cor_turno = &(game->estadoJogo.bitboard_pretas);
        }
    if(*bitboard_cor_oposta & click){
        fetch_change_board(game,click,bitboard_cor_turno,bitboard_cor_oposta);
    }
    else{
        uint64_bit * bit_piece = &(game->estadoJogo.tabuleirojogo[turno][game->pieceSelecionada]),
                   * bit_global = &(game->estadoJogo.bitboard_todas_pieces);
        efetuaJogada(bit_piece,bit_global,game->pieceCoords,click,bitboard_cor_turno);
    }   
}



void updateBitboard_ClickEvent(CorPiece turno,Pieces piece,EstadoJogo * estado,uint64_bit click){

}



void updateBitboard_SoltarEvent(CorPiece turno,Pieces piece,EstadoJogo * estado,uint64_bit click){

}