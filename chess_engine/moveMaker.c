#include "library/main.h"
#include <stdio.h>



void promotePiece(GameStruct * game , Pieces piece){
    CorPiece turno = game->turnoJogador;
    uint64_bit * bitboard_pawns = game->estadoJogo.tabuleirojogo[turno][Pawn];
    uint64_bit * bitboard_nova_piece = game->estadoJogo.tabuleirojogo[turno][piece];
    *bitboard_pawns &= ~(game->pieceCoords);
    *bitboard_nova_piece |= game->pieceCoords;
}



void clickPromotingPiece(GameStruct * game , int mouseX , int mouseY){
    game->pawnPromoted = 0;
    int offset = posTabuleiro(game->pieceCoords)%8;
    if(dentroDoBotao(mouseX,mouseY,100*offset,150*offset,100,150)){ //Queen
        promotePiece(game,Queen);
    }
    else if(dentroDoBotao(mouseX,mouseY,150*offset,200*offset,100,150)){ //Rook
        promotePiece(game,Rook);
    }
    else if(dentroDoBotao(mouseX,mouseY,100*offset,150*offset,150,200)){ //Bishop
        promotePiece(game,Bishop);
    }
    else if(dentroDoBotao(mouseX,mouseY,150*offset,200*offset,150,200)){ //Knight
        promotePiece(game,Horse);
    }
    else game->pawnPromoted = 1; //Invalid click
}



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

