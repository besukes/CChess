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




void set_new_window_size(int u, CChessSettings * settings, int window_type){
    switch(u){
        case 0: //Windowed or 1280x720
            if(window_type){ 
                if(is_window_fullscreen(settings->window)) SDL_SetWindowFullscreen(settings->window,0);
                SDL_SetWindowBordered(settings->window,SDL_TRUE);
                settings->client_settings.window_type = 0;
            }
            else{
                SDL_SetWindowSize(settings->window,1280,720);
                SDL_SetWindowPosition(settings->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
                settings->client_settings.window_res = 0;
            }
        break;
        case 1: //Windowed Borderless or 1600x900
            if(window_type){
                if(is_window_fullscreen(settings->window)) SDL_SetWindowFullscreen(settings->window,0);
                SDL_SetWindowBordered(settings->window,SDL_FALSE);
                settings->client_settings.window_type = 1;
            }
            else{
                SDL_SetWindowSize(settings->window,1600,900);
                SDL_SetWindowPosition(settings->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
                settings->client_settings.window_res = 1;
            }
        break;
        case 2: //FULLSCREEN or 1920x1080
            if(window_type){
                SDL_SetWindowBordered(settings->window,SDL_FALSE);
                SDL_SetWindowFullscreen(settings->window,SDL_WINDOW_FULLSCREEN_DESKTOP);
                settings->client_settings.window_type = 2;
            }
            else{
                SDL_SetWindowSize(settings->window,1920,1080);
                SDL_SetWindowPosition(settings->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
                settings->client_settings.window_res = 2;
            }
        break;
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
    while(*line != ' ' && *line != '\0' && *line != '\n' && counter<16){
        if(*line != 'x'){
            PlayerChessTable * table = settings->client_settings.story_st_line , * atual;
            int indx = ++ settings->client_settings.indx_starting_line;
            table = realloc(table,indx*sizeof(PlayerChessTable));

            atual = table + indx - 1;
            atual->cor_piece = brancas;
            atual->bitboard_extra_piece = (1ULL<<counter);
            atual->tipo_piece = (Pieces)get_number(line,MAX_PIECES,DEFAULT_PIECES);

            settings->client_settings.story_st_line = table;

            int n = numberChars(line);
            line = skipWhileSpace(line+n);
        }
        else line = skipWhileSpace(line+1);
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
            int indx = ++settings->client_settings.indx_selected_ults;
            UltimatesSettings * temp = realloc(settings->client_settings.selected_pieces_power,indx*sizeof(UltimatesSettings));
            (temp + indx - 1)->ultimate_refers_piece = (Pieces)counter;
            (temp + indx - 1)->ultimate = (TypeUltimate) get_number(line,MAX_ULTIMATES,DEFAULT_ULTIMATES);

            settings->client_settings.selected_pieces_power = temp;
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
        line = skip_to_x_or_value(line);
        readStartingLine(line,settings);
    }
    else if(compareString(line,"extraPiecesOwned")){
        line = skip_to_value(line);

        readExtraPieces(line,settings);
    }
    else if(compareString(line,"windowType")){
        line = skip_to_value(line);
        int u = get_number(line,2,0);
        set_new_window_size(u,settings,1);
    }
    else if(compareString(line,"windowResolution")){
        line = skip_to_value(line);
        int u = get_number(line,2,0);
        set_new_window_size(u,settings,0);
    }
}



void readLineAux(char * line , CChessSettings * settings){
    if(compareString(line,"coinsAmount")){
        line = skip_to_value(line);

        settings->ccoins_qntd = get_number(line,INT32_MAX,0);
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
    else if(compareString(line,"levelsUnlocked")){
        line = skip_to_value(line);
        settings->nivelMaxDesbloqueado = get_number(line,10,1);
    }
    else if(compareString(line,"volumeMusic")){
        line = skip_to_value(line);
        settings->client_settings.volume_music = get_number(line,101,100);
    }
    else if(compareString(line,"volumeSFX")){
        line = skip_to_value(line);
        settings->client_settings.volume_music = get_number(line,101,100);
    }
    else if(compareString(line,"themePiece")){
        line = skip_to_value(line);
        settings->client_settings.cosmeticos.themes_piece = get_number(line,2,0);
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

        settings->client_settings.cosmeticos.tabuleiroSelecionado = get_number(line,3,0);
    }
    else if(compareString(line,"selectedMusic")){
        line = skip_to_value(line);

        settings->client_settings.cosmeticos.musicaSelecionada = get_number(line,3,0);
    }
    else if(compareString(line,"checkmateEffect")){
        line = skip_to_value(line);

        settings->client_settings.cosmeticos.efeito_checkmateSelecionado = get_number(line,7,0);
    }
    else if(compareString(line,"checkEffect")){
        line = skip_to_value(line);

        settings->client_settings.cosmeticos.efeito_checkSelecionado = get_number(line,7,0);
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
                   "windowType : 0 \n"
                   "windowResolution : 0 \n"
                   "offlineTutorial : 0 \n"
                   "storyTutorial : 0 \n"
                   "mtplyTutorial : 0 \n"
                   "volumeMusic : 100 \n"
                   "volumeSFX : 100 \n"
                   "levelsUnlocked : 1 \n"
                   "themePiece : 0 \n"
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
    DIR * dir = opendir("gamefiles");
    if(dir==NULL) createGamefilesDir(settings);
    FILE * file = fopen("gamefiles/GameUserSettings.ini","w");
    int lvl_difficulty = settings->nivelDificuldade , lvl_selected = settings->nivelSelecionado ,
        selected_theme = settings->textures.temaSelecionado ,
        selected_table = settings->client_settings.cosmeticos.tabuleiroSelecionado ,
        selected_music = settings->client_settings.cosmeticos.musicaSelecionada ,
        checkmate_effect = settings->client_settings.cosmeticos.efeito_checkmateSelecionado ,
        check_effect = settings->client_settings.cosmeticos.efeito_checkSelecionado ,
        coins_amount = settings->ccoins_qntd ,
        resolution_option = settings->client_settings.window_res ,
        screen_type = settings->client_settings.window_type ,
        offline_tutorial_done = settings->tutorials.tutorial_offline_done ,
        story_tutorial_done = settings->tutorials.tutorial_story_done ,
        mtply_tutorial_done = settings->tutorials.tutorial_multiplayer_done ,
        volume_music = settings->client_settings.volume_music , max_lvl = settings->nivelMaxDesbloqueado ,
        volume_sfx = settings->client_settings.volume_sfx , theme_piece = settings->client_settings.cosmeticos.themes_piece;
    char str_pieces_place[256] = {0} , str_selected_powers[256] = {0} ,  str_owned_powers[256] = {0} , 
         str_unlocked_powers[256] = {0} , str_extra_powers_owned[256] = {0} ;
    check_pieces_place(settings,str_pieces_place);
    check_selected_powers(settings,str_selected_powers);
    check_owned_powers(settings,str_owned_powers);
    check_unlocked_powers(settings,str_unlocked_powers);
    check_extra_powers_owned(settings,str_extra_powers_owned);
    fprintf(file , "difficultyLevel : %d \n"
                   "selectedLevel : %d \n"
                   "ownedPowers : %s \n"
                   "unlockedPowers : %s \n"
                   "selectedTheme : %d \n"
                   "selectedTable : %d \n"
                   "selectedMusic : %d \n"
                   "checkmateEffect : %d \n"
                   "checkEffect : %d \n"
                   "coinsAmount : %d \n"
                   "piecesPlace : %s \n"
                   "selectedPowers : %s \n"
                   "extraPiecesOwned : %s \n"
                   "windowResolution : %d \n"
                   "windowType : %d \n"
                   "offlineTutorial : %d \n"
                   "storyTutorial : %d \n"
                   "mtplyTutorial : %d \n" 
                   "volumeMusic : %d \n"
                   "volumeSFX : %d \n"
                   "levelsUnlocked : %d \n"
                   "themePiece : %d \n",
            lvl_difficulty , lvl_selected , str_owned_powers , str_unlocked_powers , selected_theme , selected_table ,
            selected_music , checkmate_effect , check_effect , coins_amount , str_pieces_place   , str_selected_powers , str_extra_powers_owned , 
            resolution_option , screen_type ,offline_tutorial_done , story_tutorial_done , mtply_tutorial_done , volume_music , 
            volume_sfx , max_lvl , theme_piece
    );
    fclose(file);
    closedir(dir);
}
