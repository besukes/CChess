#include <library/main.h>
#include <stdlib.h>
#include <stdio.h>


// A função Search usando Negamax + Alpha-Beta
int search(GameStruct * game, int depth, int alpha, int beta, double initial_time, double time_limit , CorPiece turn) {
    if (obter_tempo_ms() - initial_time >= time_limit) {
        return FLAG_TIMEOUT;
    }
    // Quando atinge a profundidade 0 ou o jogo acaba, lê a avaliação incremental atual
    if (depth == 0 || jogo_terminou(game->estadoJogo)) {
        return evaluate(game,turn); // Devolve tab->avaliacao_incremental ajustado ao turno
    }

    Jogada jogadas[256];
    int num_jogadas = gerar_jogadas_legais(game->estadoJogo, jogadas);

    // Se não houver jogadas legais: Xeque-Mate ou Empate (Afogamento)
    if (num_jogadas == 0) {
        if (is_in_check(&game->estadoJogo,game->estadoJogo.tabuleirojogo[turn][King],turn)) {
            return -VALOR_INFINITO + depth; // Xeque-mate (prioriza mates mais rápidos)
        }
        return 0; // Empate por afogamento
    }
    int melhor_eval = -VALOR_INFINITO;
    for (int i = 0; i < num_jogadas; i++) {
        // Aplica a jogada nas Bitboards e atualiza a Avaliação Incremental (Delta)
        atualizaJogada(game,jogadas[i]);
        // Chamada recursiva do NEGAMAX:
        int eval = -search(game, depth - 1, -beta, -alpha, initial_time, time_limit, (turn == brancas) ? pretas : brancas);
        undoMove(game,jogadas[i]);
        // Se o tempo acabou em algum nó filho, propaga o timeout para cima sem salvar nada
        if (eval == FLAG_TIMEOUT) {
            return FLAG_TIMEOUT;
        }
        // Guarda a melhor pontuação encontrada para o jogador atual
        if (eval > melhor_eval) {
            melhor_eval = eval;
        }
        // Atualiza o teto mínimo garantido (Alpha)
        if (melhor_eval > alpha) {
            alpha = melhor_eval;
        }
        // 4. PODA ALPHA-BETA (Pruning):
        // Se a avaliação atual ultrapassa o Beta do adversário, ele nunca deixará esta posição acontecer.
        if (alpha >= beta) {
            break; // Para de avaliar as restantes jogadas nesta profundidade!
        }
    }
    return melhor_eval;
}