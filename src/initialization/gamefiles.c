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

#define MIN_ALLOWED 0

#define MAX_PIECES 6
#define DEFAULT_PIECES 7

#define MAX_ULTIMATES 8
#define DEFAULT_ULTIMATES 0




void checkResolutionUser(char * line , CChessSettings * settings){
    int u = get_number(line,3,0);
    switch(u){
        case 0:
            SDL_SetWindowFullscreen(settings->window,SDL_WINDOW_FULLSCREEN);
        break;
        case 1:
            SDL_SetWindowSize(settings->window,1280,720);
            SDL_SetWindowPosition(settings->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
        break;
        case 2:
            SDL_SetWindowSize(settings->window,1600,900);
            SDL_SetWindowPosition(settings->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
        break;
        case 3:
            SDL_SetWindowSize(settings->window,1920,1080);
            SDL_SetWindowPosition(settings->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
        break;
        default:break;
    }
}


void readExtraPieces(char * line ,CChessSettings * settings){
    while(*line != ' ' && *line != '\0' && *line != '\n'){
        int indx = ++settings->user_custom_items.indx_ep_owned;
        Pieces * p = settings->user_custom_items.extraPieces_owned;
        p = realloc(p,indx*sizeof(Pieces));
        *(p+indx-1) = (Pieces) get_number(line,MAX_PIECES,DEFAULT_PIECES);
        settings->user_custom_items.extraPieces_owned = p;
        int n = numberChars(line);
        line=skipWhileSpace(line+n);
        if(line==NULL) break;
    }
}


void readStartingLine(char * line ,CChessSettings * settings){
    int counter = 0;
    while(*line != ' ' && *line != '\0' && *line != '\n'){
        if(*line != 'x'){
            PlayerChessTable * table = settings->story_st_line , * atual;
            int indx = ++ settings->indx_starting_line;
            table = realloc(table,indx*sizeof(PlayerChessTable));

            atual = table + indx - 1;
            atual->cor_piece = brancas;
            atual->bitboard_extra_piece = (1ULL<<counter);
            atual->tipo_piece = (Pieces)get_number(line,MAX_PIECES,DEFAULT_PIECES);

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
            TypeUltimate * temp = realloc(settings->user_custom_items.ultimates_unlocked,indx*sizeof(TypeUltimate));
            *(temp + indx - 1) = (TypeUltimate) get_number(line,MAX_ULTIMATES,DEFAULT_ULTIMATES);

            settings->user_custom_items.ultimates_unlocked = temp;
        }
        else if(type==2){
            int indx = ++settings->indx_selected_ults;
            UltimatesSettings * temp = realloc(settings->selected_pieces_power,indx*sizeof(UltimatesSettings));
            (temp + indx - 1)->ultimate_refers_piece = (Pieces)counter;
            (temp + indx - 1)->ultimate = (TypeUltimate) get_number(line,MAX_ULTIMATES,DEFAULT_ULTIMATES);

            settings->selected_pieces_power = temp;
        }
        else{
            int indx = ++settings->user_custom_items.indx_ult_owned;
            TypeUltimate * temp = settings->user_custom_items.ultimates_owned;
            temp = realloc(temp,indx*sizeof(TypeUltimate));
            *(temp + indx - 1) = (TypeUltimate) get_number(line,MAX_ULTIMATES,DEFAULT_ULTIMATES);
            settings->user_custom_items.ultimates_owned = temp;
        }
        int n = numberChars(line);
        line = skipWhileSpace(line+n);
        counter++;
        if(line == NULL) break;
    }
}



void readLineAuxAux(char * line , CChessSettings * settings){
    if(compareString(line,"ownedPowers")){
        line = skip_to_value(line);
        
        readPowersLine(line,settings,0);
    }
    else if(compareString(line,"unlockedPowers")){
        line = skip_to_value(line);

        readPowersLine(line,settings,1);
    }
    else if(compareString(line,"selectedPowers")){
        line = skip_to_value(line);

        readPowersLine(line,settings,2);
    }
    else if(compareString(line,"piecesPlace")){
        line = skip_to_value(line);

        readStartingLine(line,settings);
    }
    else if(compareString(line,"extraPiecesOwned")){
        line = skip_to_value(line);

        readExtraPieces(line,settings);
    }
    else if(compareString(line,"resolutionOption")){
        line = skip_to_value(line);
        checkResolutionUser(line,settings);
    }
}



void readLineAux(char * line , CChessSettings * settings){
    if(compareString(line,"coinsAmount")){
        line = skip_to_value(line);

        settings->cosmeticos.efeito_checkSelecionado = get_number(line,INT32_MAX,0);
    }
    else if(compareString(line,"offlineTutorial")){
        line = skip_to_value(line);
        settings->tutorials.tutorial_offline_done = get_number(line,1,0);
    }
    else if(compareString(line,"storyTutorial")){
        line = skip_to_value(line);
        settings->tutorials.tutorial_story_done = get_number(line,1,0);
    }
    else if(compareString(line,"mtplyTutorial")){
        line = skip_to_value(line);
        settings->tutorials.tutorial_multiplayer_done = get_number(line,1,0);
    }
    else readLineAuxAux(line,settings);
}



void readLine(char * line , CChessSettings * settings){
    if(compareString(line,"difficultyLevel")){
        line = skip_to_value(line);

        settings->nivelDificuldade = get_number(line,6,0);
    }
    else if(compareString(line,"selectedLevel")){
        line = skip_to_value(line);

        settings->nivelDificuldade = get_number(line,15,0);
    }
    else if(compareString(line,"selectedTheme")){
        line = skip_to_value(line);

        settings->textures.temaSelecionado = get_number(line,2,0);
    }
    else if(compareString(line,"selectedTable")){
        line = skip_to_value(line);

        settings->cosmeticos.tabuleiroSelecionado = get_number(line,3,0);
    }
    else if(compareString(line,"selectedMusic")){
        line = skip_to_value(line);

        settings->cosmeticos.musicaSelecionada = get_number(line,3,0);
    }
    else if(compareString(line,"checkmateEffect")){
        line = skip_to_value(line);

        settings->cosmeticos.efeito_checkmateSelecionado = get_number(line,7,0);
    }
    else if(compareString(line,"checkEffect")){
        line = skip_to_value(line);

        settings->cosmeticos.efeito_checkSelecionado = get_number(line,7,0);
    }
    else readLineAux(line,settings);
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
                   "extraPiecesOwned : 7 \n"
                   "resolutionOption : 0 \n"
                   "offlineTutorial : 0 \n"
                   "storyTutorial : 0 \n"
                   "mtplyTutorial : 0 \n"
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
        closedir(dir);
    }
}


void writeNewGameFiles(CChessSettings * settings){
    
}