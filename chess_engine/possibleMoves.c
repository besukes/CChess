#include "library/main.h"



void king_line_dependant_moves(uint64_bit * atk ,uint64_bit (*func)(uint64_bit,int),uint64_bit pos , uint64_bit colunaA , uint64_bit colunaH){
        *atk |= func(pos,8);
        *atk |= func(pos&~colunaA,7);
        *atk |= func(pos&~colunaA,9);
}

uint64_bit get_king_moves(uint64_bit pos,uint64_bit bitboard_pieces,CorPiece turno){
    int posTab = posTabuleiro(pos);
    uint64_bit at = 0 , colunaA = 0 , colunaH = 0;
    getColunasAH(&colunaA,&colunaH);
    if(0<=posTab && posTab<8) king_line_dependant_moves(&at,&shiftl,pos,colunaA,colunaH);
    else if(56<=posTab && posTab<64) king_line_dependant_moves(&at,&shiftr,pos,colunaA,colunaH);
    else {
        king_line_dependant_moves(&at,&shiftl,pos,colunaA,colunaH);
        king_line_dependant_moves(&at,&shiftr,pos,colunaA,colunaH);
    }
    at |= ((pos & ~colunaA)>>1);
    at |= ((pos & ~colunaH)<<1);
    return at;
}



uint64_bit get_possible_pawn_attacks(uint64_bit pos,uint64_bit bitboard_pieces,CorPiece turno,uint64_bit (*func)(uint64_bit,int),GameStruct * game){
    uint64_bit oposto = (turno==brancas) ? game->estadoJogo.bitboard_pretas : game->estadoJogo.bitboard_brancas;
    uint64_bit fst_step = func(pos,8) & ~bitboard_pieces;
    if(pawnFirstRank(pos,turno)){
        uint64_bit snd_step = (fst_step) ? ( func(pos,16) & ~bitboard_pieces ) : 0;
        return ( fst_step | snd_step | ( get_pawn_attacks(pos,turno) & oposto) );
    }
    else{
        return ( fst_step | ( get_pawn_attacks(pos,turno) & oposto) );
    }
}


uint64_bit get_piece_attacks(uint64_bit pos,Pieces piece,GameStruct * game){
    uint64_bit bitboardPieces = game->estadoJogo.bitboard_todas_pieces;
    CorPiece cor = game->turnoJogador;
    switch(piece){
        case Pawn :
            uint64_bit (*func)(uint64_bit,int) = (cor==brancas) ? &shiftl : &shiftr;
            return get_possible_pawn_attacks(pos,bitboardPieces,cor,func,game);
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
            return get_king_moves(pos,bitboardPieces,cor);
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


int isPseudoValidMove(GameStruct * game, uint64_bit drop , Boolean * castle){
    Pieces piece = game->pieceSelecionada;
    CorPiece cor = game->turnoJogador;
    uint64_bit pos_piece = game->pieceCoords,
               pos_atacks = get_piece_attacks(pos_piece,piece,game),
               pos_mesma_cor = get_same_colour_bitboard(&(game->estadoJogo),cor);
    uint64_bit jogada = (~pos_mesma_cor & (pos_atacks & drop));
    *castle = game->pieceSelecionada == King && is_castelling_king(pos_piece,game,cor);
    return (jogada != 0 || *castle);
}
