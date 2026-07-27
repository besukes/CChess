#include <library/main.h>
#include <stdio.h>

//alpha usually starts at -99999 , int alpha = -99999; --Current best white evaluation
//beta usually starts at 99999 , int beta = 99999; --Current best black evaluation
//alpha - white eval , beta - black eval

Moves get_best_move(GameStruct * game , CorPiece turn){
    int depth = MAX_DEPTH_SEARCH , ai_level = 0;
    int pieces_eval[2][NUMBER_PIECES] = {};
    int black_eval = 0 , white_eval = 0;
    initializeStructs(pieces_eval,NUMBER_PIECES);
    evaluate(game,turn,ai_level,pieces_eval,&white_eval,&black_eval);
    Moves best_move = move_algorithm(game,turn,depth,ai_level,-99999,99999,white_eval,black_eval,pieces_eval);
    printf("[engine] get_best_move: piece %d from %d to %d eval %d\n", best_move.piece_type, posTabuleiro(best_move.last_piece_pos), posTabuleiro(best_move.move), best_move.move_evaluation);
    return (best_move);
}


Moves move_algorithm(GameStruct * game , CorPiece turn , int depth , int ai_level , int alpha , int beta , int weval , int beval , int evals[2][NUMBER_PIECES]){
    uint64_bit positional_best_move = 0; //No move to start with
    SearchInfo search = {.ai_level = ai_level , .alpha = alpha , .beta = beta, .depth = depth , 
                        .bot_colour = turn , .turn = turn , .white_eval = weval , .black_eval = beval
                        };
    Pieces best_piece = 0, piece = 0;
    uint64_bit current_pos = 0, best_pos = 0;
    int cur_best_alpha = alpha , cur_best_beta = beta;
    for(int i=NUMBER_PIECES - 1;i>=0;i--){
        int counter=0;
        piece = (Pieces)i;
        uint64_bit piece_bitboard = game->estadoJogo.tabuleirojogo[turn][piece];
        search.piece_type = piece;
        int moves_for_piece = 0; //Remove
        while(piece_bitboard != 0){
            if( (piece_bitboard & 1ULL) != 0){
                current_pos = 1ULL<<counter;
                uint64_bit current_attacks = get_piece_attacks(current_pos,piece,game,turn) & (~get_same_colour_bitboard(&game->estadoJogo,turn));
                Moves best_searched = search_algorithm(current_pos,current_attacks,game,evals,&search);
                if(best_searched.move_evaluation > cur_best_alpha && turn == brancas){
                    search.alpha = best_searched.move_evaluation;
                    cur_best_alpha = search.alpha;
                    positional_best_move = best_searched.move;
                    best_piece = piece;
                    best_pos = current_pos;
                }
                else if(best_searched.move_evaluation < cur_best_beta && turn == pretas){
                    search.beta = best_searched.move_evaluation;
                    cur_best_beta = search.beta;
                    positional_best_move = best_searched.move;
                    best_piece = piece;
                    best_pos = current_pos;
                }
            }
            counter++;
            piece_bitboard>>=1;
            if(search.alpha>=search.beta) break;
        }
    }
    //ret_eval tem que dar a avaliacao do turno oposto para depois search.c recursiva funcionar como deve
    int ret_eval = (turn==brancas) ? search.alpha : search.beta;
    Moves ret = {.move = positional_best_move , .move_evaluation = ret_eval , .piece_type = best_piece , .last_piece_pos = best_pos};
    return ret;
}