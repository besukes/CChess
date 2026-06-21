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