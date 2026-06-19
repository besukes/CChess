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




void readPowersLine(char * line , CChessSettings * settings, int type){

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
}



void readGameFilesSettings(struct dirent * entry , CChessSettings * settings){
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
                   "ownedPowers : None \n"
                   "unlockedPowers : None \n"
                   "selectedTheme : 0 \n"
                   "selectedTable : 0 \n"
                   "selectedMusic : 0 \n"
                   "checkmateEffect : 0 \n"
                   "checkEffect : 0 \n"
                   "selectedPowers : None None None None None None\n"
                   "coinsAmount : 0\n"
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
                readGameFilesSettings(entry,settings);
            }
        }
         if(!found) addGamefilesFile(settings);
    }
    closedir(dir);
}