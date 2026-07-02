#include "library/main.h"



void update_en_passant(GameStruct * game){
    CorPiece turno = game->turnoJogador;
    if(pawnFirstRank(game->pieceCoords,turno) && game->pieceSelecionada == Pawn){
        game->estadoJogo.enpassant = (turno==brancas) ? (game->pieceCoords << 8) : (game->pieceCoords >> 8);
    }
    else game->estadoJogo.enpassant = 0;
}



Boolean can_en_passant(GameStruct * game , uint64_bit drop,CorPiece cor){
    if(game->pieceSelecionada != Pawn) return 0;
    int pos_tab_drop = posTabuleiro(drop) , pos_tab_piece = posTabuleiro(game->pieceCoords);
    if(cor==brancas){
       Boolean is_6_line = 40<=pos_tab_drop && pos_tab_drop < 48 ,
               pawn_in_pos = 32<=pos_tab_piece && pos_tab_piece < 40;
       return (is_6_line && pawn_in_pos && ((game->estadoJogo.enpassant & drop) != 0));
    }
    else{
        Boolean is_3_line = 16<=pos_tab_drop && pos_tab_drop < 24,
                pawn_in_pos = pawn_in_pos = 24<=pos_tab_piece && pos_tab_piece < 32;
        return (is_3_line && pawn_in_pos && ((game->estadoJogo.enpassant & drop) != 0));
    }
}


void enpassant_move(GameStruct * game , uint64_bit * cor_oposta , uint64_bit * mesma_cor,ShiftFunction ep_shift){
    uint64_bit peao_removido = ep_shift(game->estadoJogo.enpassant,8);
    (*cor_oposta) &= ~peao_removido;
    (*mesma_cor) = ((*mesma_cor & ~game->pieceCoords) | game->estadoJogo.enpassant);
    game->estadoJogo.bitboard_todas_pieces = *mesma_cor | *cor_oposta;

    CorPiece turno = game->turnoJogador , op = (turno==brancas) ? pretas : brancas;
    uint64_bit peoes_turno = game->estadoJogo.tabuleirojogo[turno][0],
               peoes_opostos = game->estadoJogo.tabuleirojogo[op][0];
    peoes_turno = (peoes_turno & ~game->pieceCoords) | game->estadoJogo.enpassant;
    peoes_opostos &= ~peao_removido;

    game->estadoJogo.tabuleirojogo[turno][0] = peoes_turno;
    game->estadoJogo.tabuleirojogo[op][0] = peoes_opostos;
    game->estadoJogo.enpassant = 0;
}

