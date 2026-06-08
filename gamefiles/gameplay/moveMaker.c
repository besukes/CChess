#include "library/main.h"
#include <stdio.h>





void efetuaJogada(uint64_bit * selected_piece , uint64_bit * todas_pieces , uint64_bit original_coords , uint64_bit click , uint64_bit * mesmacor){
    *mesmacor = ( ( (*mesmacor) & (~original_coords) ) | click);
    *selected_piece = ( ( (*selected_piece) & (~original_coords) ) | click);
    *todas_pieces = ( ( (*todas_pieces) & (~original_coords)) | click);
}



void fetch_change_board(GameStruct * game,uint64_bit click,uint64_bit * mesmaCor , uint64_bit * corOposta){
    CorPiece turno = game->turnoJogador;
    CorPiece cor_oposta = (turno == brancas) ? pretas : brancas;
    int i;
    Pieces piece_comida , selected = game->pieceSelecionada;
    for(i=0;i<6 && !(game->estadoJogo.tabuleirojogo[cor_oposta][i] & click);i++);
    if(i==6) printf("[ERROR] In function fetch_change_board\n");
    else{
        piece_comida = (Pieces)i;
        addHeadLinkedList(&(game->lastmoves),piece_comida,click,cor_oposta);
        game->estadoJogo.tabuleirojogo[cor_oposta][i] &= ~(click);
        *corOposta &= ~click;
        efetuaJogada(&(game->estadoJogo.tabuleirojogo[turno][selected]),
                     &(game->estadoJogo.bitboard_todas_pieces),game->pieceCoords,
                     click,mesmaCor
                    );
    }
}



void castle_King(GameStruct * game , uint64_bit click , int square, uint64_bit * mesmaCor){
    int pos = posTabuleiro(click) , offset = 0 , shiftam = 3;
    CorPiece turno = game->turnoJogador;
    uint64_bit (*funcRook)(uint64_bit,int) = &shiftl,
               (*funcKing)(uint64_bit,int) = &shiftr;
    if(pos%8 > 4){
        offset=7;funcRook = &shiftr; shiftam = 2; funcKing = &shiftl;
    }
    uint64_bit rooks = game->estadoJogo.tabuleirojogo[turno][Rook],
               rook_de_castle = 1ULL<<(square + offset),
               rook_shifted = funcRook(rook_de_castle,shiftam);

    *mesmaCor = *mesmaCor & ~rooks;
    game->estadoJogo.bitboard_todas_pieces &= ~rooks;

    rooks = rook_shifted | (rooks & ~rook_de_castle);
    game->estadoJogo.tabuleirojogo[turno][Rook] = rooks;
    uint64_bit click_shifted = funcKing(rook_shifted,1);

    *mesmaCor |= rooks;
    game->estadoJogo.bitboard_todas_pieces |= rooks;
    game->estadoJogo.tabuleirojogo[turno][King] = click_shifted;
}


void checkTurno(CorPiece turno , uint64_bit * * oposta , uint64_bit * * mesma_cor,int * sq , GameStruct * game , uint64_bit (**ep)(uint64_bit,int)){
    if(turno==brancas){
        *oposta = &(game->estadoJogo.bitboard_pretas);
        *mesma_cor = &(game->estadoJogo.bitboard_brancas);
        *sq=0;
        *ep = &shiftr;
    }
    else{
        *oposta = &(game->estadoJogo.bitboard_brancas);
        *mesma_cor = &(game->estadoJogo.bitboard_pretas);
        *sq=56;
        *ep = &shiftl;
    }
}

void atualizaJogada(GameStruct * game , uint64_bit click,Boolean castles,Boolean enpassant){
    CorPiece turno = game->turnoJogador;
    uint64_bit * bitboard_cor_oposta , * bitboard_cor_turno , (*ep)(uint64_bit,int);
    int square;
    checkTurno(turno,&bitboard_cor_oposta,&bitboard_cor_turno,&square,game,&ep);
    if(castles){
        castle_King(game,click,square,bitboard_cor_turno);
        game->estadoJogo.canCastle[turno][Short] = 0;
        game->estadoJogo.canCastle[turno][Long] = 0;
    }
    else if(enpassant){
        enpassant_move(game,bitboard_cor_oposta,bitboard_cor_turno,ep);
    }
    else if(*bitboard_cor_oposta & click){
        fetch_change_board(game,click,bitboard_cor_turno,bitboard_cor_oposta);
    }
    else{
        uint64_bit * bit_piece = &(game->estadoJogo.tabuleirojogo[turno][game->pieceSelecionada]),
                   * bit_global = &(game->estadoJogo.bitboard_todas_pieces);
        efetuaJogada(bit_piece,bit_global,game->pieceCoords,click,bitboard_cor_turno);
    }   
}



void updateBitboard_ClickEvent(CorPiece turno,Pieces piece,EstadoJogo * estado,uint64_bit click){

}



void updateBitboard_SoltarEvent(CorPiece turno,Pieces piece,EstadoJogo * estado,uint64_bit click){

}