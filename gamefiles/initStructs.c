#include "library/main.h"



EstadoJogo initEstadoJogo(void){
    EstadoJogo es;
    es.checkMate = 0;
    es.checkBrancas = 0;
    es.checkPretas = 0;
    initTabuleiro(es.tabuleiroJogoPretas,0);
    initTabuleiro(es.tabuleiroJogoBrancas,5);
    es.maxIndxBrancas = 10;
    es.maxIndxMemoriaB = 32;
    es.posicoesAfetadasBrancas = initPosicoesAfetadasBrancas(5);
    es.maxIndxPretas = 10;
    es.maxIndxMemoriaP = 32;
    es.posicoesAfetadasPretas = initPosicoesAfetadasPretas(0);
}