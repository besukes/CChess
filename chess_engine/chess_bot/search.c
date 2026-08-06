#include <library/main.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define NO_FLAGS 0
#define FLAG_ONLY_CAPTURES 1



int applyDeltaMove(GameStruct * game , Jogada * jogada , CorPiece turn){
    CorPiece op_turn = (turn == brancas) ? pretas : brancas;
    uint64_bit origem_bit = 1ULL << jogada->origem;
    uint64_bit destino_bit = 1ULL << jogada->destino;
    Pieces peca_movida = (Pieces)jogada->peca_movida;
    int old_moved_eval = evaluate_piece(origem_bit, peca_movida, turn, game);

    Pieces peca_capturada = Empty;
    for(int i=0;i<NUMBER_PIECES;i++){
        if(game->estadoJogo.tabuleirojogo[op_turn][i] & destino_bit){
            peca_capturada = (Pieces)i;
            break;
        }
    }
    int old_captured_eval = (peca_capturada != Empty) ? evaluate_piece(destino_bit, peca_capturada, op_turn, game) : 0;

    atualizaJogada(game, jogada, turn);

    int new_moved_eval = evaluate_piece(destino_bit, peca_movida, turn, game);

    int who2Move = (turn == brancas) ? 1 : -1;
    return (who2Move * (new_moved_eval - old_moved_eval + old_captured_eval));
}


int quiescence(GameStruct * game, int alpha, int beta, int quiescence_eval, CorPiece turn){
    if (quiescence_eval >= beta) return beta;
    if (alpha < quiescence_eval) alpha = quiescence_eval;

    Jogada jogadas[256];
    int num_jogadas = gerar_jogadas_legais(game, jogadas, turn, FLAG_ONLY_CAPTURES); // idealmente só capturas aqui
    for (int i = 0; i < num_jogadas; i++){
        int delta = applyDeltaMove(game,&jogadas[i],turn);
        int eval = -quiescence(game, -beta, -alpha, quiescence_eval + delta, (turn==brancas)?pretas:brancas);
        undoMove(game,&jogadas[i],turn);
        if (eval >= beta) return beta;
        if (eval > alpha) alpha = eval;
    }
    return alpha;
}


// A função Search usando Negamax + Alpha-Beta
int search(GameStruct * game, int depth, int alpha, int beta, int wb_eval , double initial_time, double time_limit , CorPiece turn){
    if (SDL_GetTicks() - initial_time >= time_limit) {
        return FLAG_TIMEOUT;
    }
    if (depth == 0) { // Quando atinge a profundidade 0 ou o jogo acaba, lê a avaliação incremental atual
        return quiescence(game, alpha, beta, wb_eval, turn);
    }
    Jogada jogadas[256];int num_jogadas = gerar_jogadas_legais(game, jogadas,turn, NO_FLAGS);
    if (num_jogadas == 0) { // Se não houver jogadas legais: Xeque-Mate ou Empate (Afogamento)
        if (is_in_check(&game->estadoJogo,game->estadoJogo.tabuleirojogo[turn][King],turn)) {
            return -VALOR_INFINITO + depth; // Xeque-mate (prioriza mates mais rápidos)
        }
        return 0; // Empate por afogamento
    }
    for (int i = 0; i < num_jogadas; i++) {
        int delta = applyDeltaMove(game,&jogadas[i],turn);
        // Chamada recursiva do NEGAMAX:
        int eval = -search(game, depth - 1, -beta, -alpha, wb_eval + delta, initial_time, time_limit, (turn == brancas) ? pretas : brancas);
        undoMove(game,&jogadas[i],turn);
        // Se o tempo acabou em algum nó filho, propaga o timeout para cima sem salvar nada
        if ((-eval) == FLAG_TIMEOUT) {
            return FLAG_TIMEOUT;
        }
        // 4. PODA ALPHA-BETA (Pruning):
        // Se a avaliação atual ultrapassa o Beta do adversário, ele nunca deixará esta posição acontecer.
        if (eval >= beta) {
            return beta;
        }
        alpha = (eval > alpha) ? eval : alpha; // Atualiza o Alpha se a avaliação atual for melhor
    }
    return alpha;
}