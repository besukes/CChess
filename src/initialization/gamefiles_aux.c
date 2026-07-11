#include "library/main.h"
#include <stdlib.h>



void check_extra_powers_owned(CChessSettings * settings , char * str){
    Pieces * extra = settings->user_custom_items.extraPieces_owned;
    if(extra == NULL) return;
    int indx = settings->user_custom_items.indx_ep_owned;
    for(int i=0;i<indx;i++){
        Pieces atual = *(extra + i);
        sprintf(str,"%s%d ",str,atual);
    }
}


void check_unlocked_powers(CChessSettings * settings , char * str){
    TypeUltimate * unlocked = settings->user_custom_items.ultimates_unlocked;
    if(unlocked == NULL) return;
    int indx = settings->user_custom_items.indx_ult_unlocked;
    for(int i=0;i<indx;i++){
        TypeUltimate atual = *(unlocked + i);
        sprintf(str,"%s%d ",str,atual);
    }
}

void check_owned_powers(CChessSettings * settings , char * str){
    TypeUltimate * owned = settings->user_custom_items.ultimates_owned;
    if(owned == NULL) return;
    int indx = settings->user_custom_items.indx_ult_owned;
    for(int i=0;i<indx;i++){
        TypeUltimate atual = *(owned + i);
        sprintf(str,"%s%d ",str,atual);
    }
}

void check_selected_powers(CChessSettings * settings , char * str){
    UltimatesSettings * selected = settings->selected_pieces_power;
    if(selected == NULL) return;
    int indx = settings->indx_selected_ults;
    for(int i=0;i<indx;i++){
        UltimatesSettings * atual = selected + i;
        sprintf(str,"%s%d ",str,atual->ultimate);
    }
}


void check_pieces_place(CChessSettings * settings , char * str){
    PlayerChessTable * table = settings->story_st_line;
    int indx = settings->indx_starting_line , counter_indx = 0;
    if(table == NULL) return;
    for(int i=0;i<16;i++){
        if(counter_indx >= indx || (table + counter_indx)->bitboard_extra_piece != (1ULL<<i)) 
            sprintf(str,"%sx ",str);
        else{
            PlayerChessTable * atual = table + counter_indx;
            sprintf(str,"%s%d ",str,atual->tipo_piece);
            counter_indx++;
        }
    }
}