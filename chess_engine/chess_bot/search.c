#include <library/main.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>


// A função Search usando Negamax + Alpha-Beta
int search(GameStruct * game, int depth, int alpha, int beta, double initial_time, double time_limit , CorPiece turn){
    /*if (SDL_GetTicks() - initial_time >= time_limit) {
        return FLAG_TIMEOUT;
    }*/
    if (depth == 0) { // Quando atinge a profundidade 0 ou o jogo acaba, lê a avaliação incremental atual
        return evaluate(game,turn);
    }
    Jogada jogadas[256];int num_jogadas = gerar_jogadas_legais(game, jogadas,turn);
    if (num_jogadas == 0) { // Se não houver jogadas legais: Xeque-Mate ou Empate (Afogamento)
        if (is_in_check(&game->estadoJogo,game->estadoJogo.tabuleirojogo[turn][King],turn)) {
            return -VALOR_INFINITO + depth; // Xeque-mate (prioriza mates mais rápidos)
        }
        return 0; // Empate por afogamento
    }
    for (int i = 0; i < num_jogadas; i++) {
        atualizaJogada(game,&jogadas[i],turn);
        // Chamada recursiva do NEGAMAX:
        int eval = -search(game, depth - 1, -beta, -alpha, initial_time, time_limit, (turn == brancas) ? pretas : brancas);
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