#include <library/main.h>
#include <stdlib.h>
#include <stdio.h>


int depth_search(GameStruct * game , SearchInfo * search_info , int piece_evals[2][NUMBER_PIECES] , int cur_piece_eval){
    int cur_alpha = search_info->alpha , cur_beta = search_info->beta;
    int white_eval = search_info->white_eval , black_eval = search_info->black_eval;
    evaluate_pos(game,search_info,&white_eval,&black_eval,piece_evals,cur_piece_eval);
    if(search_info->depth <= 0) return ((search_info->turn == brancas) ? cur_alpha : cur_beta); 
    int new_turn = (search_info->turn == brancas) ? pretas : brancas;
    return move_algorithm(game,new_turn,search_info->depth-1,search_info->ai_level,cur_alpha,cur_beta,white_eval,black_eval,piece_evals).move_evaluation;
    //necessita de verificar o turno atual e aplicar a melhor jogada , decrementando o turno e fazendo recursividade para procurar
    //os proximos melhor moves
    //secalhar utilizar a funcao move_algorithm e fazer algumas alteracoes
}


Moves search_algorithm (uint64_bit posi , uint64_bit atks , GameStruct * game ,int piece_evals[2][NUMBER_PIECES] , SearchInfo * search_info){
    int cntr = 0;
    uint64_bit casa_atual = 0 , bst = 0;
    CorPiece turn = search_info->turn;
    int piece_eval = piece_evals[turn][search_info->piece_type];
    MoveInfo mov = {.piece_moved =search_info->piece_type,.turn = turn , .last_piece_pos = posi};
    while(atks!=0){
        if(atks & 1ULL){
            casa_atual = 1ULL<<cntr;
            // Save board snapshot to validate undo
            uint64_bit snap_all = game->estadoJogo.bitboard_todas_pieces;
            uint64_bit snap_white = game->estadoJogo.bitboard_brancas;
            uint64_bit snap_black = game->estadoJogo.bitboard_pretas;
            uint64_bit snap_tab_white[6], snap_tab_black[6];
            for(int si=0;si<6;si++){ snap_tab_white[si] = game->estadoJogo.tabuleirojogo[brancas][si]; snap_tab_black[si] = game->estadoJogo.tabuleirojogo[pretas][si]; }
            atualizaJogada(game,casa_atual,0,0,&mov);
            if(!is_in_check(&game->estadoJogo,game->estadoJogo.tabuleirojogo[turn][King],turn)){
                int new_eval = depth_search(game,search_info,piece_evals,piece_eval);
                if(new_eval > search_info->alpha && search_info->turn == brancas){
                    search_info->alpha = new_eval;
                    bst = casa_atual;
                    printf("[search] updated alpha to %d for piece %d from %d to %d\n", new_eval, search_info->piece_type, posTabuleiro(posi), posTabuleiro(bst));
                }
                else if(new_eval < search_info->beta && search_info->turn == pretas){
                    search_info->beta = new_eval;
                    bst = casa_atual;
                    printf("[search] updated beta to %d for piece %d from %d to %d\n", new_eval, search_info->piece_type, posTabuleiro(posi), posTabuleiro(bst));
                }
            }
            undoMove(game,casa_atual,posi,0,search_info->piece_type,search_info->turn);
            // Validate undo restored snapshot
            if(game->estadoJogo.bitboard_todas_pieces != snap_all || game->estadoJogo.bitboard_brancas != snap_white || game->estadoJogo.bitboard_pretas != snap_black){
                printf("[search][ERROR] board not restored after undo. before all=%llu white=%llu black=%llu\n", (unsigned long long)snap_all, (unsigned long long)snap_white, (unsigned long long)snap_black);
                printf("[search][ERROR] after all=%llu white=%llu black=%llu\n", (unsigned long long)game->estadoJogo.bitboard_todas_pieces, (unsigned long long)game->estadoJogo.bitboard_brancas, (unsigned long long)game->estadoJogo.bitboard_pretas);
                for(int si=0;si<6;si++){
                    if(game->estadoJogo.tabuleirojogo[brancas][si] != snap_tab_white[si] || game->estadoJogo.tabuleirojogo[pretas][si] != snap_tab_black[si]){
                        printf("[search][ERROR] piece %d mismatch. white before=%llu after=%llu black before=%llu after=%llu\n", si, (unsigned long long)snap_tab_white[si], (unsigned long long)game->estadoJogo.tabuleirojogo[brancas][si], (unsigned long long)snap_tab_black[si], (unsigned long long)game->estadoJogo.tabuleirojogo[pretas][si]);
                    }
                }
            }
            piece_evals[turn][search_info->piece_type] = piece_eval;
        }
        atks>>=1; 
        cntr++;
    }
    int eval =(search_info->turn == brancas) ? search_info->alpha : search_info->beta;
    Moves ret = {.move = bst , .move_evaluation = eval , .last_piece_pos = posi , .piece_type = search_info->piece_type};
    if(bst == 0) printf("[search] no legal move found for piece %d at %d\n", search_info->piece_type, posTabuleiro(posi));
    return ret;
}