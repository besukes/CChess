#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>




int minimum(int n1,int n2){
    return ((n1<n2)? n1 : n2);
}



Pieces comparePiece(EstadoJogo estado , CorPiece cor , uint64_bit posclique){
    int i;
    for(i=0;i<6;i++){
        if(estado.tabuleirojogo[cor][i] & posclique){
            return((Pieces)i);
        }
    }
    return Empty;
}



int dentroDoBotao(int mx , int my , int inf_x , int sup_x , int inf_y , int sup_y){
    return ( (inf_x<=mx && mx<=sup_x) && (inf_y <= my && my<=sup_y));
}


int posTabuleiro(uint64_bit bitboard){
    if(bitboard==0) return (-1);
    return __builtin_ctzll(bitboard);
}



int calcPosClique(int lower_border_limit , int upper_border_limit , int pos , int square_size , int type){
    int c = (type) ? 0 : 7;
    for(int i = lower_border_limit ; i <= upper_border_limit ; i+=square_size){
        if(i <= pos && pos < i + square_size){
            return c;
        }
        if(type) c++;
        else c--;
    }
    return (-1);
}



uint64_bit click_table_position(int mouseX , int mouseY){
    uint64_bit p = 0;
    int infHorizontal = 260 , supHorizontal = 1060 ,
        infVertical = 140 , supVertical = 940;
    int tamanhoQuadrado = 100;
    int cx = calcPosClique(infHorizontal,supHorizontal,mouseX,tamanhoQuadrado,1) , 
        cy = calcPosClique(infVertical,supVertical,mouseY,tamanhoQuadrado,0);
    if(cx!=(-1) && cy != (-1)){
        p = (1ULL<<((cy*8)+cx));
    }
    return p;
}



void addHeadLinkedList(PecasComidasLL * list , Pieces piece_comida , uint64_bit pos_piece , CorPiece cor){
    PecasComidasLL novo = malloc(sizeof(struct PecasComidas));
    novo->cor_piece = cor;
    novo->pos_de_piece = pos_piece;
    novo->tipo_piece = piece_comida;
    novo->prox = *list;
    *list = novo;
}


void freeLinkedList(PecasComidasLL list){
    PecasComidasLL cur = list;
    while(cur){
        PecasComidasLL next = cur->prox;
        free(cur);
        cur = next;
    }
}


void removeHeadLinkedList(PecasComidasLL * list){
    PecasComidasLL u = *list;
    *list = (*list)->prox;
    free(u);
}


void getColunasAH(uint64_bit * colunaA , uint64_bit * colunaH){
    *colunaA = 0ULL;
    *colunaH = 0ULL;
    for(int i=0;i<8;i++){
        *colunaA |= (1ULL<< (8*i));
        *colunaH |= (1ULL<< (8*i + 7));
    }
}




int compareString(char comparing[],char compared[]){
    int i;
    for(i=0; comparing[i] != '\0' && comparing[i] !=' ' && comparing[i] != '\n' && compared[i] != '\0' && comparing[i] == compared[i] ; i++);
    if(compared[i] == '\0') return 1;
    return 0;
}

char * skipWhileSpace(char * str){
    int i;
    for(i=0;str[i] == ' ';i++);
    if(str[i] == '\0' || str[i] == '\n') return NULL;
    return (str + i);
}


int numberChars(char * str){
    int i=0;
    while(str[i] != '\0' && str[i]!= ' '  && str[i]!= '\n') i++;
    return i;
}


int exponente(int base , int expo){
    int numbr = 1;
    for(int i=0;i<expo;i++){
        numbr*=base;
    }
    return numbr;
}


int strToNumber(char * str){
    int numbr = 0;
    while (*str != '\0' && *str != ' ' && *str != '\n') {
        numbr = (numbr * 10) + (*str - '0'); 
        str++;
    }
    return numbr;
}


int strToNumber_esp(char * str){
    int n_char = numberChars(str) , numbr = 0;
    for(;n_char>0;n_char--){
        numbr += (*str - 48)*exponente(10,n_char-1);
        str++;
    }
    return numbr;
}


char * skip_to_value(char * line){
    for(;*line<'0' || *line>'9';line++){
        if(*line == '\0' || *line == '\n') return NULL;
    }
    return line;
}


int get_number(char * line, int max , int def){
    int numbr = strToNumber(line);
    if(numbr < 0 || numbr>max ) numbr = def;
    return numbr;
}

