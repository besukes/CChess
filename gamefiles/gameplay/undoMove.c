#include "library/main.h"



void undoPieceComida(GameStruct * game , uint64_bit * bb_cor_piece_comida, uint64_bit click){
    uint64_bit pos_ant = game->lastmoves->pos_de_piece;
    game->estadoJogo.tabuleirojogo[game->lastmoves->cor_piece][game->lastmoves->tipo_piece] |= pos_ant;
    *bb_cor_piece_comida |= pos_ant;
    game->estadoJogo.bitboard_todas_pieces |= pos_ant;
}


void undoPiece_move(GameStruct * game , uint64_bit * mesma_cor,uint64_bit cor_oposta, uint64_bit click){
    uint64_bit * piece_tab = &(game->estadoJogo.tabuleirojogo[game->turnoJogador][game->pieceSelecionada]);
    *piece_tab = ((*piece_tab & ~click) | game->pieceCoords);
    *mesma_cor = ((*mesma_cor & ~click) | game->pieceCoords);
    game->estadoJogo.bitboard_todas_pieces = *mesma_cor | cor_oposta;
}


void undoMove(GameStruct * game , uint64_bit click){
    CorPiece cor = game->turnoJogador;
    uint64_bit mesma_cor = game->estadoJogo.bitboard_brancas, cor_oposta = game->estadoJogo.bitboard_pretas;
    if(cor){
        mesma_cor = game->estadoJogo.bitboard_pretas;
        cor_oposta = game->estadoJogo.bitboard_brancas;
    }
    undoPiece_move(game,&mesma_cor,cor_oposta,click);
    undoPieceComida(game,&cor_oposta,click);
}