#include "library/main.h"



void undoPieceComida(GameStruct * game , uint64_bit * bb_cor_piece_comida, uint64_bit click){
    game->estadoJogo.tabuleirojogo[game->lastmoves->cor_piece][game->lastmoves->tipo_piece] |= click;
    *bb_cor_piece_comida |= click;
    game->estadoJogo.bitboard_todas_pieces |= click;
}


void restauraCastle(uint64_bit * rei_tab,uint64_bit * mesma_cor, uint64_bit click , GameStruct * game , CorPiece turno){
    int offset = 0;
    if(turno==pretas) offset = 7;
    uint64_bit nova_rook , antiga_pos_rook;
    //Short castle
    if(posTabuleiro(click)%8 > 4){
        nova_rook = (1ULL<< (8*offset + F1));
        antiga_pos_rook = (1ULL<<(8*offset + H1));
    }
    //Long castle
    else{
        nova_rook = (1ULL<< (8*offset + D1));
        antiga_pos_rook = (1ULL<<(8*offset + A1));
    }
    uint64_bit rei_atual = *rei_tab;
    *rei_tab = (1ULL<<(8*offset + E1));
    *mesma_cor = (*mesma_cor & ~nova_rook & ~rei_atual) | antiga_pos_rook | *rei_tab;
    game->estadoJogo.tabuleirojogo[turno][Rook] &= ~nova_rook;
    game->estadoJogo.tabuleirojogo[turno][Rook] |= antiga_pos_rook;

    uint64_bit cor_oposta = (turno == brancas) ? game->estadoJogo.bitboard_pretas : game->estadoJogo.bitboard_brancas;
    game->estadoJogo.bitboard_todas_pieces = *mesma_cor | cor_oposta;
}


void undoPiece_move(GameStruct * game , uint64_bit * mesma_cor,uint64_bit * cor_oposta, uint64_bit click,Boolean castles){
    uint64_bit * piece_tab = &(game->estadoJogo.tabuleirojogo[game->turnoJogador][game->pieceSelecionada]);
    if(castles){
        restauraCastle(piece_tab,mesma_cor,click,game,game->turnoJogador);
    }
    else{
        *piece_tab = ((*piece_tab & ~click) | game->pieceCoords);
        *mesma_cor = ((*mesma_cor & ~click) | game->pieceCoords);
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
}