#include "library/main.h"






uint64_bit shiftr(uint64_bit pos,int shift){
    return (pos>>shift);
}



uint64_bit shiftl(uint64_bit pos,int shift){
    return (pos<<shift);
}



void get_attacks(int max , uint64_bit (*func)(uint64_bit,int),uint64_bit pos_limites,uint64_bit pos_piece,int shift ,uint64_bit * atk){
    *atk = 0;
    for(int i=1;i<=max ;i++){
        uint64_bit casa_atual = func(pos_piece,shift*i);
        *(atk) |= casa_atual;
        if(pos_limites & casa_atual) break;
    }
}



uint64_bit get_cross_attacks(uint64_bit piece_pos , uint64_bit pos_limites){
    int indx_tab = posTabuleiro(piece_pos);
    uint64_bit quadrado = initQuadrado();
    pos_limites |= quadrado;
    int linha = indx_tab/8 , coluna = indx_tab % 8,
        maxDistNorte = 7-linha,
        maxDistSul= linha,
        maxDistOeste = coluna,
        maxDistEste = 7-coluna;
    uint64_bit atkN,atkS,atkO,atkE ,atk= 0;
    get_attacks(maxDistNorte,&shiftl,pos_limites,piece_pos,8,&atkN);
    get_attacks(maxDistSul,&shiftr,pos_limites,piece_pos,8,&atkS);
    get_attacks(maxDistOeste,&shiftr,pos_limites,piece_pos,1,&atkO);
    get_attacks(maxDistEste,&shiftl,pos_limites,piece_pos,1,&atkE);
    atk = atkN | atkS | atkO | atkE;
    return atk;
}



uint64_bit get_sliding_attacks(uint64_bit piece_pos, uint64_bit pos_limites){
    int indx_tab = posTabuleiro(piece_pos);
    int linha = indx_tab/8 , coluna = indx_tab % 8,
        maxDistNordeste = minimum(7-linha,7-coluna),
        maxDistNoroeste = minimum(7-linha,coluna),
        maxDistSudeste = minimum(linha,7-coluna),
        maxDistSudoeste = minimum(linha,coluna);
    uint64_bit atkNo,atkNe,atkSude ,atkSudo,atk;
    get_attacks(maxDistNordeste,&shiftl,pos_limites,piece_pos,9,&atkNe);
    get_attacks(maxDistNoroeste,&shiftl,pos_limites,piece_pos,7,&atkNo);
    get_attacks(maxDistSudeste,&shiftr,pos_limites,piece_pos,7,&atkSude);
    get_attacks(maxDistSudoeste,&shiftr,pos_limites,piece_pos,9,&atkSudo);
    atk = atkNe | atkNo | atkSude | atkSudo;
    return atk;
}



uint64_bit get_pawn_attacks(uint64_bit piece_pos,CorPiece cor){
    uint64_bit at = 0 , colunaA = 0 , colunaH = 0;
    getColunasAH(&colunaA,&colunaH);
    if(cor==brancas){
        at |= ((piece_pos<<9) & ~colunaA);
        at |= ((piece_pos<<7) & ~colunaH);
    }
    else{
        at |= ((piece_pos>>9) & ~colunaH);
        at |= ((piece_pos>>7) & ~colunaA);
    }
    return at;
}



uint64_bit get_knight_attacks(uint64_bit piece_pos){
    uint64_bit at = 0 , colunaA = 0 , colunaH = 0 ,
               colunaB = 0 , colunaG = 0;
    for(int i=0;i<8;i++){
        colunaA |= (1ULL<< (8*i));
        colunaB |= (1ULL<< (8*i + 1));
        colunaH |= (1ULL<< (8*i + 7));
        colunaG |= (1ULL<< (8*i + 6));
    }
    at |= ((piece_pos & ~colunaA & ~colunaB )<<6);
    at |= ((piece_pos & ~colunaA)<<15);
    at |= ((piece_pos & ~colunaH & ~colunaG )<<10);
    at |= ((piece_pos & ~colunaH)<<17);
    at |= ((piece_pos & ~colunaG & ~colunaH)>>6);
    at |= ((piece_pos& ~colunaH)>>15);
    at |= ((piece_pos & ~colunaA & ~colunaB)>>10);
    at |= ((piece_pos& ~colunaA)>>17);
    return at;
}



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

}


int isCheckMate(EstadoJogo * estado , uint64_bit pos_king , uint64_bit cor){

}


TipoJogada check_or_mate(GameStruct * game){
    TipoJogada j = Valid;
    CorPiece turno_op = (game->turnoJogador) ? brancas : pretas;
    uint64_bit pos_king_op = game->estadoJogo.tabuleirojogo[turno_op][King];
    if(is_in_check(&(game->estadoJogo),pos_king_op,turno_op)){
        game->estadoJogo.king_in_check[turno_op] = 1;
        if(isCheckMate(&(game->estadoJogo),pos_king_op,turno_op)){
            j = Checkmate;
        }
        else j = Invalid;
    }
    return j;
}
