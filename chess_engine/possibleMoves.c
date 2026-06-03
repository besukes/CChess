#include "library/main.h"

uint64_bit get_cross_attacks(uint64_bit piece_pos){
    int indx_tab = posTabuleiro(piece_pos);
    int linha = indx_tab/8 , coluna = indx_tab % 8,
        maxDistNorte = 7-linha,
        maxDistSul= linha,
        maxDistOeste = coluna,
        maxDistEste = 7-coluna;
    uint64_bit atk = 0;
    for(int i=1;i<=maxDistNorte;i++){
        atk |= (piece_pos<<(8*i));
    }
    for(int i=1;i<=maxDistSul;i++){
        atk |= (piece_pos>>(8*i));
    }
    for(int i=1;i<=maxDistOeste;i++){
        atk |= (piece_pos>>i);
    }
    for(int i=1;i<=maxDistEste;i++){
        atk |= (piece_pos<<i);
    }
    return atk;
}

uint64_bit get_sliding_attacks(uint64_bit piece_pos){
    int indx_tab = posTabuleiro(piece_pos);
    int linha = indx_tab/8 , coluna = indx_tab % 8,
        maxDistNordeste = minimum(7-linha,7-coluna),
        maxDistNoroeste = minimum(7-linha,coluna),
        maxDistSudeste = minimum(linha,7-coluna),
        maxDistSudoeste = minimum(linha,coluna);
    uint64_bit atk = 0;
    for(int i=1;i<=maxDistNordeste;i++){
        atk |= (piece_pos<<(9*i));
    }
    for(int i=1;i<=maxDistNoroeste;i++){
        atk |= (piece_pos<<(7*i));
    }
    for(int i=1;i<=maxDistSudeste;i++){
        atk |= (piece_pos>>(7*i));
    }
    for(int i=1;i<=maxDistSudoeste;i++){
        atk |= (piece_pos>>(9*i));
    }
    return atk;
}

uint64_bit get_pawn_attacks(uint64_bit piece_pos){
    uint64_bit at = 0 , colunaA = 0 , colunaH = 0;
    for(int i=0;i<8;i++){
        colunaA |= (1ULL<< (8*i));
        colunaH |= (1ULL<< (8*i + 7));
    }
    at |= ((piece_pos<<9) & ~colunaA);
    at |= ((piece_pos<<7) & ~colunaH);
    return at;
}

uint64_bit get_knight_attacks(uint64_bit piece_pos){
    uint64_bit at = 0 , colunaA = 0 , colunaH = 0 ,
               colunaB = 0 , colunaG = 0;
    for(int i=0;i<8;i++){
        colunaA |= (1ULL<< (8*i));
        colunaB |= (1ULL<< (8*i) + 1);
        colunaH |= (1ULL<< (8*i + 7));
        colunaG |= (1ULL<< (8*i + 6));
    }
    at |= ((piece_pos<<6) & ~colunaA & ~colunaB);
    at |= ((piece_pos<<15) & ~colunaA);
    at |= ((piece_pos<<10) & ~colunaH & ~colunaG);
    at |= ((piece_pos<<17) & ~colunaH);
    at |= ((piece_pos>>6) & ~colunaG & ~colunaH);
    at |= ((piece_pos>>15) & ~colunaH);
    at |= ((piece_pos>>10) & ~colunaA & ~colunaB);
    at |= ((piece_pos>>17) & ~colunaA);
    return at;
}

Boolean is_in_check(EstadoJogo * estado , uint64_bit kingpos , CorPiece cor){
    uint64_bit op_knight = estado->tabuleirojogo[cor][2].bitboard_position,
               op_pawns = estado->tabuleirojogo[cor][0].bitboard_position,
               op_rooks = estado->tabuleirojogo[cor][1].bitboard_position,
               op_bishops = estado->tabuleirojogo[cor][3].bitboard_position,
               op_queen = estado->tabuleirojogo[cor][4].bitboard_position;
    Boolean check_knights = get_knights_attacks(kingpos) & op_knight,
            check_pawns = get_pawn_attacks(kingpos) & op_pawns,
            check_diagonals = get_sliding_attacks(kingpos) & (op_bishops | op_queen),
            check_cross = get_cross_attacks(kingpos) & (op_rooks | op_queen);
    return (check_knights && check_pawns && check_diagonals && check_cross);
}

