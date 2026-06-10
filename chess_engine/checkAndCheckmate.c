#include "library/main.h"
#include <stdio.h>



Boolean is_in_check(EstadoJogo * estado , uint64_bit kingpos , CorPiece cor){
    uint64_bit todas_pieces =  estado->bitboard_todas_pieces;
    CorPiece oponente = (cor==brancas) ? pretas : brancas;
    uint64_bit op_knight = estado->tabuleirojogo[oponente][2],
               op_pawns = estado->tabuleirojogo[oponente][0],
               op_rooks = estado->tabuleirojogo[oponente][1],
               op_bishops = estado->tabuleirojogo[oponente][3],
               op_queen = estado->tabuleirojogo[oponente][4];
    uint64_bit check_knights = get_knight_attacks(kingpos) & op_knight,
               check_pawns = get_pawn_attacks(kingpos,cor) & op_pawns,
               check_diagonals = get_sliding_attacks(kingpos,todas_pieces) & (op_bishops | op_queen),
               check_cross = get_cross_attacks(kingpos,todas_pieces) & (op_rooks | op_queen);
    return ( (check_knights | check_pawns | check_diagonals | check_cross ) != 0);
}



void notInCheck(GameStruct * game){
    CorPiece turno = game->turnoJogador;
    game->estadoJogo.king_in_check[turno] = 0;
}


void initgame_aux(GameStruct * game_aux , CorPiece cor_pieces_teste , Pieces piece_atual , uint64_bit pos_piece_atual){
    game_aux->turnoJogador = cor_pieces_teste;
    game_aux->pieceSelecionada = piece_atual;
    game_aux->pieceCoords = pos_piece_atual;
    game_aux->lastmoves = NULL;
}


int isCheckMate(GameStruct * game , uint64_bit pos_king , uint64_bit cor){
    int pos_tab = 0 , in_check = 1;
    uint64_bit same_colour = get_same_colour_bitboard(&(game->estadoJogo),cor);
    for(int i=0;i<6 && in_check;i++){
        pos_tab = 0;
        uint64_bit tab_piece = game->estadoJogo.tabuleirojogo[cor][i];
        Pieces piece_atual = (Pieces)i;
        while(tab_piece !=0 && in_check){
            if(tab_piece & 1ULL){
                uint64_bit pos_piece = (1ULL<<pos_tab);
                uint64_bit pieces_move = get_piece_attacks(pos_piece,piece_atual,game);
                uint64_bit tries = pieces_move & ~same_colour;
                while( tries !=0 && in_check){
                    GameStruct game_aux = *game;
                    initgame_aux(&game_aux,cor,piece_atual,pos_piece);
                    Boolean castles = 0 , enpassant = 0;
                    int casa_destino = __builtin_ctzll(tries);
                    uint64_bit drop = 1ULL<<casa_destino;
                    if(isPseudoValidMove(&game_aux,drop,&castles,&enpassant)){
                        atualizaJogada(&game_aux,drop,castles,enpassant);
                        in_check = is_in_check(&(game_aux.estadoJogo),(game_aux.estadoJogo.tabuleirojogo[cor][King]),cor);
                    }
                    tries &= (tries-1);
                }
            }
            tab_piece = tab_piece>>1;
            pos_tab++;
        }
    }
    return (in_check);
}




TipoJogada check_or_mate(GameStruct * game, Boolean castles , uint64_bit click){
    TipoJogada j = Valid;
    CorPiece turno = game->turnoJogador;
    CorPiece turno_op = (turno == pretas) ? brancas : pretas;
    uint64_bit pos_king_op = game->estadoJogo.tabuleirojogo[turno_op][King];
    if(is_in_check(&(game->estadoJogo),pos_king_op,turno_op)){
        if(isCheckMate(game,pos_king_op,turno_op)){
            j = Checkmate;
            printf("Rei em CHECKMATE\n");
        }
        game->estadoJogo.king_in_check[turno_op] = 1;
    }
    
    if(is_in_check(&(game->estadoJogo),game->estadoJogo.tabuleirojogo[turno][King],turno)){
        return Invalid;
    }
    else if(invalidCastle(game,castles,click)){
        return Invalid;;
    }
    else{
        verifica_direito_castle(game,turno);
    }
    return j;
}
