#include "library/main.h"



uint64_bit get_king_moves(uint64_bit pos,uint64_bit bitboard_pieces){

}



uint64_bit get_possible_pawn_attacks(uint64_bit pos,uint64_bit bitboard_pieces,CorPiece turno){
    if(pawnFirstRank(pos,turno)){
        return ( ( ( (pos<<8) | (pos<<16) ) & ~bitboard_pieces ) | get_pawn_attacks(pos,turno));
    }
    else{
        return ( ( (pos<<8)  & ~bitboard_pieces ) | get_pawn_attacks(pos,turno));
    }
}


uint64_bit get_piece_attacks(uint64_bit pos,Pieces piece,GameStruct * game){
    uint64_bit bitboardPieces = game->estadoJogo.bitboard_todas_pieces;
    switch(piece){
        case Pawn :
            return get_possible_pawn_attacks(pos,bitboardPieces,game->turnoJogador);
        break;
        case Rook :
            return get_cross_attacks(pos,bitboardPieces);
        break;
        case Horse :
            return get_knight_attacks(pos);
        break;
        case Bishop :
            return get_sliding_attacks(pos,bitboardPieces);
        break;
        case Queen :
            return (get_sliding_attacks(pos,bitboardPieces) | get_cross_attacks(pos,bitboardPieces));
        break;
        case King :
            return get_king_moves(pos,bitboardPieces);
        break;
        default :
            return 0ULL;
        break;
    }
}


uint64_bit get_same_colour_bitboard(EstadoJogo * estado , CorPiece cor){
    if(cor==brancas) return estado->bitboard_brancas;
    else return estado->bitboard_pretas;
}


int isPseudoValidMove(GameStruct * game, uint64_bit drop){
    Pieces piece = game->pieceSelecionada;
    CorPiece cor = game->turnoJogador;
    uint64_bit pos_piece = game->estadoJogo.tabuleirojogo[cor][piece],
               pos_atacks = get_piece_attacks(pos_piece,piece,game),
               pos_mesma_cor = get_same_colour_bitboard(&(game->estadoJogo),cor);
    uint64_bit bool = (~pos_mesma_cor & (pos_atacks & drop) );
    return (bool != 0);
}
