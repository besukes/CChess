#include "library/main.h"



void update_en_passant(GameStruct * game){
    CorPiece turno = game->turnoJogador;
    if(pawnFirstRank(game->pieceCoords,turno)){
        game->estadoJogo.enpassant = (turno==brancas) ? (game->pieceCoords >> 8) : (game->pieceCoords << 8);
    }
}



Boolean can_en_passant(GameStruct * game , uint64_bit drop,CorPiece cor){
    int pos_tab = posTabuleiro(drop);
    if(cor==brancas){
       Boolean is_7_line = 48<=pos_tab && pos_tab < 56;
       return (is_7_line && ((game->estadoJogo.enpassant & drop) != 0));
    }
    else{
        Boolean is_1_line = 8<=pos_tab && pos_tab < 16;
        return (is_1_line && ((game->estadoJogo.enpassant & drop) != 0));
    }
}


void enpassant_move(GameStruct * game , uint64_bit * cor_oposta , uint64_bit * mesma_cor,ShiftFunction ep_shift){
    (*cor_oposta) = ((*cor_oposta & ~ep_shift(game->estadoJogo.enpassant,8)));
    (*mesma_cor) = ((*mesma_cor & ~game->pieceCoords) | game->estadoJogo.enpassant);
    game->estadoJogo.bitboard_todas_pieces = *mesma_cor | *cor_oposta;
}