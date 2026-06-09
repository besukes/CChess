#include "library/main.h"




Boolean is_in_check(EstadoJogo * estado , uint64_bit kingpos , CorPiece cor){
    uint64_bit todas_pieces =  estado->bitboard_todas_pieces;
    CorPiece oponente = (cor==brancas) ? pretas : brancas;
    uint64_bit op_knight = estado->tabuleirojogo[oponente][2],
               op_pawns = estado->tabuleirojogo[oponente][0],
               op_rooks = estado->tabuleirojogo[oponente][1],
               op_bishops = estado->tabuleirojogo[oponente][3],
               op_queen = estado->tabuleirojogo[oponente][4];
    Boolean check_knights = get_knight_attacks(kingpos) & op_knight,
            check_pawns = get_pawn_attacks(kingpos,cor) & op_pawns,
            check_diagonals = get_sliding_attacks(kingpos,todas_pieces) & (op_bishops | op_queen),
            check_cross = get_cross_attacks(kingpos,todas_pieces) & (op_rooks | op_queen);
    return (check_knights || check_pawns || check_diagonals || check_cross);
}


void notInCheck(GameStruct * game){
    CorPiece turno = game->turnoJogador;
}


int isCheckMate(EstadoJogo * estado , uint64_bit pos_king , uint64_bit cor){

}


TipoJogada check_or_mate(GameStruct * game, Boolean castles , uint64_bit click){
    TipoJogada j = Valid;
    CorPiece turno = game->turnoJogador;
    CorPiece turno_op = (turno) ? brancas : pretas;
    uint64_bit pos_king_op = game->estadoJogo.tabuleirojogo[turno_op][King];
    if(is_in_check(&(game->estadoJogo),game->estadoJogo.tabuleirojogo[turno][King],turno) || invalidCastle(game,castles,click)){
        game->estadoJogo.king_in_check[turno] = 1;
        j = Invalid;
    }
    else if(isCheckMate(&(game->estadoJogo),pos_king_op,turno_op)) j = Checkmate;
    else if(game->pieceSelecionada == King){
        game->estadoJogo.canCastle[turno][Short] = 0;
        game->estadoJogo.canCastle[turno][Long] = 0;
    }
    return j;
}
