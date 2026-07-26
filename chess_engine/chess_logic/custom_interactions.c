#include "library/main.h"
#include <stdlib.h>



int is_protected_square(GameStruct * game , uint64_bit click){
    CorPiece turno_atual = game->turnoJogador;
    for(int i=0; i < game->estadoJogo.indx_extra_pieces ; i++){
        ExtraPieces * p = game->estadoJogo.tabuleiroExtraPieces + i;
        if(p->tipo_piece == TheDog && (p->cor_piece != turno_atual)){
            if((get_dog_protected_squares(p->bitboard_extra_piece,p->cor_piece) & click) != 0) return 1;
        }
    }
    return 0;
}


uint64_bit get_dog_attacks(uint64_bit pos_dog){
    return get_king_moves(pos_dog);
}


uint64_bit get_dog_protected_squares(uint64_bit pos_dog ,CorPiece turno){
    int posTab = posTabuleiro(pos_dog);
    uint64_bit prot = 0 , colunaA = 0 , colunaH = 0;
    getColunasAH(&colunaA,&colunaH);
    uint64_bit (*shift_pos)(uint64_bit,int) = (turno==brancas) ? &shiftl : &shiftr;
    Boolean black_dog_1st_line = 56<=posTab && posTab<64 && turno==pretas ,
            white_dog_8th_line = 56<=posTab && posTab<64 && turno==brancas;
    if(!(black_dog_1st_line || white_dog_8th_line)) {
        king_line_dependant_moves(&prot,shift_pos,pos_dog,colunaA,colunaH);
    }
    return prot;
}