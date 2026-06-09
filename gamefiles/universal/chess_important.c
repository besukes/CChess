#include "library/main.h"



uint64_bit shiftr(uint64_bit pos,int shift){
    return (pos>>shift);
}



uint64_bit shiftl(uint64_bit pos,int shift){
    return (pos<<shift);
}


int pawnFirstRank(uint64_bit pos,CorPiece cor){
    int postab = __builtin_ctzll(pos);
    if(cor==brancas){
        return(8 <= postab && postab < 16);
    }
    else{
        return( 48 <= postab && postab < 56);
    }
}


int is_open_castle_path(uint64_bit bitboard_todas_pieces,uint64_bit path , uint64_bit extraPositions){
    uint64_bit relevant_path = path & ~extraPositions;
    return ( (bitboard_todas_pieces & relevant_path )== 0);
}


int is_castelling_king(uint64_bit pos_piece , GameStruct * game , CorPiece cor, uint64_bit drop){
    uint64_t destino_short = (cor == brancas) ? (1ULL << 6 | 1ULL<<7)  : (1ULL << 62 | 1ULL<<63),
             destino_long  = (cor == brancas) ? (1ULL << 2 | 1ULL <<1 | 1ULL)  : (1ULL << 58 | 1ULL << 57 | 1ULL << 56);
    Boolean castelShort = ( (destino_short & drop) != 0) && 
                is_open_castle_path(game->estadoJogo.bitboard_todas_pieces,destino_short,game->estadoJogo.tabuleirojogo[cor][Rook]),
            castelLong = ( (destino_long & drop) != 0) && 
                is_open_castle_path(game->estadoJogo.bitboard_todas_pieces,destino_long,game->estadoJogo.tabuleirojogo[cor][Rook]);
    return (                                      !game->estadoJogo.king_in_check[cor] &&
            ( (castelShort && game->estadoJogo.canCastle[cor][Short]) || (castelLong && game->estadoJogo.canCastle[cor][Long]) ) );
}


int invalidCastle(GameStruct * game , Boolean castles , uint64_bit click){
    return 0;
}
