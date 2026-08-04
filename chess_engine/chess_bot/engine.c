#include <library/main.h>
#include <stdio.h>
#include <SDL2/SDL.h>

//alpha usually starts at -99999 , int alpha = -99999; --Current best white evaluation
//beta usually starts at 99999 , int beta = 99999; --Current best black evaluation
//alpha - white eval , beta - black eval

typedef struct jogadabot{
    Jogada best_move;
    int move_eval;
    int move_time;
}jogadabot;


jogadabot engine_search(GameStruct * game , CorPiece turn , int depth){
    Jogada jogadas[256];
    int num_jogadas = gerar_jogadas_legais(game, jogadas);
    int melhor_eval = -VALOR_INFINITO;
    int initial_time = SDL_GetTicks();
    Jogada best_move = {.origem = 0, .destino = 0, .peca_movida = Empty, .peca_capturada = Empty, .promocao = 0, .especial = 0};
    for (int i = 0; i < num_jogadas; i++) {
        // Aplica a jogada nas Bitboards e atualiza a Avaliação Incremental (Delta)
        atualizaJogada(game,&jogadas[i],turn);
        // Chamada recursiva do NEGAMAX:
        int eval = -search(game, depth - 1, -VALOR_INFINITO, VALOR_INFINITO, initial_time, initial_time + 1000, (turn == brancas) ? pretas : brancas);
        undoMove(game,&jogadas[i],turn);
        // Se o tempo acabou em algum nó filho, propaga o timeout para cima sem salvar nada
        if(eval == FLAG_TIMEOUT) {
            printf("[engine] engine_search: timeout reached during search\n");
            return (jogadabot){{.origem = 64, .destino = 64, .peca_movida = Empty, .peca_capturada = Empty, .promocao = 0, .especial = 0}
                                , FLAG_TIMEOUT
                                , SDL_GetTicks() - initial_time};
        }
        // Guarda a melhor pontuação encontrada para o jogador atual
        if(eval > melhor_eval) {
            melhor_eval = eval;
            best_move = jogadas[i];
        }
    }
    jogadabot result = {.best_move = best_move,.move_eval = melhor_eval ,.move_time = SDL_GetTicks() - initial_time};
    return result;
}



Jogada get_best_move(GameStruct * game , CorPiece turn){
    int depth = MAX_DEPTH_SEARCH;
    jogadabot best_move = engine_search(game,turn,depth);
    if(best_move.move_eval == FLAG_TIMEOUT) printf("[engine] get_best_move: timeout reached during search\n");
    else printf("[engine] get_best_move: piece %d from %d to %d , took %d ms with an eval of %d\n", best_move.best_move.peca_movida, 
                    posTabuleiro(best_move.best_move.origem), posTabuleiro(best_move.best_move.destino), best_move.move_time, best_move.move_eval);
    return (best_move.best_move);
}

