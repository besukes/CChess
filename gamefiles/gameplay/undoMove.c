#include "library/main.h"



void undoPieceComida(GameStruct * game , uint64_bit bb_cor_oposta , uint64_bit bb_cor_piece_comida, uint64_bit click){

}


void undoPiece_move(GameStruct * game , uint64_bit mesma_cor , uint64_bit cor_oposta, uint64_bit click){

}


void undoMove(GameStruct * game , uint64_bit click){
    CorPiece cor = game->turnoJogador;
    uint64_bit mesma_cor = game->estadoJogo.bitboard_brancas, cor_oposta = game->estadoJogo.bitboard_pretas;
    if(cor){
        mesma_cor = game->estadoJogo.bitboard_pretas;
        cor_oposta = game->estadoJogo.bitboard_brancas;
    }
    undoPiece_move(game,mesma_cor,cor_oposta,click);
    undoPieceComida(game,mesma_cor,cor_oposta,click);
}