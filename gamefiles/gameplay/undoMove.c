#include "library/main.h"



void undoPieceComida(GameStruct * game , uint64_bit * bb_cor_piece_comida, uint64_bit click){
        uint64_bit pos_ant = game->lastmoves->pos_de_piece;
        game->estadoJogo.tabuleirojogo[game->lastmoves->cor_piece][game->lastmoves->tipo_piece] |= pos_ant;
        *bb_cor_piece_comida |= pos_ant;
        game->estadoJogo.bitboard_todas_pieces |= pos_ant;
}


void restauraCastle(uint64_bit * mesma_cor, uint64_bit click , GameStruct * game , CorPiece turno){
    int offset = 0;
    if(turno==pretas) offset = 7;
    uint64_bit nova_rook , antiga_pos_rook;
    //Short castle
    if(click%8 > 4){
        nova_rook = (1ULL<< (8*offset + F1));
        antiga_pos_rook = (1ULL<<(8*offset + H1));
    }
    //Long castle
    else{
        nova_rook = (1ULL<< (8*offset + D1));
        antiga_pos_rook = (1ULL<<(8*offset + A1));
    }
    *mesma_cor = (*mesma_cor & ~nova_rook) | antiga_pos_rook;
    game->estadoJogo.tabuleirojogo[turno][Rook] &= ~nova_rook;
    game->estadoJogo.tabuleirojogo[turno][Rook] |= antiga_pos_rook;
}


void undoPiece_move(GameStruct * game , uint64_bit * mesma_cor,uint64_bit * cor_oposta, uint64_bit click,Boolean castles){
    uint64_bit * piece_tab = &(game->estadoJogo.tabuleirojogo[game->turnoJogador][game->pieceSelecionada]);
    *piece_tab = ((*piece_tab & ~click) | game->pieceCoords);
    *mesma_cor = ((*mesma_cor & ~click) | game->pieceCoords);
    if(castles){
        restauraCastle(mesma_cor,click,game,game->turnoJogador);
    }
    game->estadoJogo.bitboard_todas_pieces = *mesma_cor | *cor_oposta;
}


void undoMove(GameStruct * game , uint64_bit click,Boolean castles){
    CorPiece cor = game->turnoJogador;
    uint64_bit * mesma_cor = &(game->estadoJogo.bitboard_brancas), 
               * cor_oposta = &(game->estadoJogo.bitboard_pretas);
    if(cor == pretas){
        mesma_cor = &(game->estadoJogo.bitboard_pretas);
        cor_oposta = &(game->estadoJogo.bitboard_brancas);
    }
    undoPiece_move(game,mesma_cor,cor_oposta,click,castles);
    if(game->lastmoves != NULL && game->lastmoves->pos_de_piece == click) undoPieceComida(game,cor_oposta,click);
    game->estadoJogo.king_in_check[game->turnoJogador] = 0;
}