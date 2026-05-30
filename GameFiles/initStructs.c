#include "main.h"


PecaTabuleiro * initTabuleiro(PecaTabuleiro pt[32]){

}


EstadoJogo initEstadoJogo(void){
    EstadoJogo es;
    es.quantidadePecasJogo = 32;
    initTabuleiro(es.tabuleiroJogo);
    es.posicoesAfetadasPretas = initPosicoesAfetadasPretas(0);
    es.posicoesAfetadasBrancas = initPosicoesAfetadasBrancas(5);
    es.maxIndxBrancas = 2;
    es.maxIndxPretas = 2;
}