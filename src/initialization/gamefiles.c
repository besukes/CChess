#include "library/main.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
    #define create_dir(path) _mkdir(path)
#else 
    #define create_dir(path) mkdir(path, 0777)
#endif



void readStartingLine(char * line ,CChessSettings * settings){
    int counter = 0;
    while(*line != ' ' && *line != '\0' && *line != '\n'){
        if(*line != 'x'){
            PlayerChessTable * table = settings->story_st_line , * atual;
            int indx = settings->indx_starting_line;
            table = realloc(table,(size_t)indx);

            atual = table + indx - 1;
            atual->cor_piece = brancas;
            atual->bitboard_extra_piece = (1ULL<<counter);
            atual->tipo_piece = (Pieces)strToNumber(line);

            settings->story_st_line = table;
        }
        int n = numberChars(line);
        line = skipWhileSpace(line+n);
        counter++;
        if(line == NULL) break;
    }
}


void readPowersLine(char * line , CChessSettings * settings, int type){
    int counter = 0;
    while(*line != ' ' && *line != '\0' && *line != '\n'){
        if(type==1){
            int indx = ++settings->user_custom_items.indx_ult_unlocked;
            TypeUltimate * temp = realloc(settings->user_custom_items.ultimates_unlocked,(size_t)indx);
            *(temp + indx - 1) = (TypeUltimate) strToNumber(line);

            settings->user_custom_items.ultimates_unlocked = temp;
        }
        else if(type==2){
            int indx = ++settings->indx_selected_ults;
            UltimatesSettings * temp = realloc(settings->selected_pieces_power,(size_t)indx);
            (temp + indx - 1)->ultimate_refers_piece = (Pieces)counter;
            (temp + indx - 1)->ultimate = (TypeUltimate) strToNumber(line);

            settings->selected_pieces_power = temp;
        }
        else{
            int indx = ++settings->user_custom_items.indx_ult_owned;
            TypeUltimate * temp = settings->user_custom_items.ultimates_owned;
            temp = realloc(temp,(size_t)indx);
            *(temp + indx - 1) = (TypeUltimate) strToNumber(line);
            settings->user_custom_items.ultimates_owned = temp;
        }
        int n = numberChars(line);
        line = skipWhileSpace(line+n);
        counter++;
        if(line == NULL) break;
    }
}



void readLine(char * line , CChessSettings * settings){
    if(compareString(line,"difficultyLevel")){
        line+=18;
        settings->nivelDificuldade = strToNumber(line);
    }
    else if(compareString(line,"selectedLevel")){
        line+=16;
        settings->nivelDificuldade = strToNumber(line);
    }
    else if(compareString(line,"ownedPowers")){
        line+=14;
        readPowersLine(line,settings,0);
    }
    else if(compareString(line,"unlockedPowers")){
        line+=17;
        readPowersLine(line,settings,1);
    }
    else if(compareString(line,"selectedPowers")){
        line+=17;
        readPowersLine(line,settings,2);
    }
    else if(compareString(line,"selectedTheme")){
        line+=16;
        settings->textures.temaSelecionado = strToNumber(line);
    }
    else if(compareString(line,"selectedTable")){
        line+=16;
        settings->cosmeticos.tabuleiroSelecionado = strToNumber(line);
    }
    else if(compareString(line,"selectedMusic")){
        line+=16;
        settings->cosmeticos.musicaSelecionada = strToNumber(line);
    }
    else if(compareString(line,"checkmateEffect")){
        line+=18;
        settings->cosmeticos.efeito_checkmateSelecionado = strToNumber(line);
    }
    else if(compareString(line,"checkEffect")){
        line+=14;
        settings->cosmeticos.efeito_checkSelecionado = strToNumber(line);
    }
    else if(compareString(line,"coinsAmount")){
        line+=14;
        settings->cosmeticos.efeito_checkSelecionado = strToNumber(line);
    }
    else if(compareString(line,"piecesPlace")){
        line+=14;
        readStartingLine(line,settings);
    }
}



void readGameFilesSettings(CChessSettings * settings){
    char path[267];
    snprintf(path,sizeof(path),"gamefiles/GameUserSettings.ini");
    FILE * file = fopen(path,"r");
    char line[512];
    while(fgets(line,sizeof(line),file)){
        readLine(line,settings);
    }
    fclose(file);
}


void writeDefaultGamefiles(FILE * file){
    fprintf(file , "difficultyLevel : 0 \n"
                   "selectedLevel : 0 \n"
                   "ownedPowers : 0 \n"
                   "unlockedPowers : 0 \n"
                   "selectedTheme : 0 \n"
                   "selectedTable : 0 \n"
                   "selectedMusic : 0 \n"
                   "checkmateEffect : 0 \n"
                   "checkEffect : 0 \n"
                   "coinsAmount : 0 \n"
                   "piecesPlace : x x 7 5 x 2 x x 0 x 0 0 0 0 0 x \n"
                   "selectedPowers : 0 0 0 0 0 0 0 \n"
           )
    ;
}


void addGamefilesFile(CChessSettings * settings){
    FILE *ficheiro = NULL;
    ficheiro = fopen("gamefiles/GameUserSettings.ini", "w");
    writeDefaultGamefiles(ficheiro);
    fclose(ficheiro);

    initGameFiles(settings);
}


void createGamefilesDir(CChessSettings * settings){
    create_dir("gamefiles");
    addGamefilesFile(settings);
}


void initGameFiles(CChessSettings * settings){
    struct dirent * entry;
    DIR * dir = opendir("gamefiles");
    int found=0;
    if(dir==NULL) createGamefilesDir(settings);
    else{
        while((entry = readdir(dir)) != NULL && !found){
            if(strcmp(entry->d_name,"GameUserSettings.ini") == 0){
                found=1;
                readGameFilesSettings(settings);
            }
        }
         if(!found) addGamefilesFile(settings);
    }
    closedir(dir);
}