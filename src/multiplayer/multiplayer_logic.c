#include "library/main.h"
#include <stdio.h>


void handleMultiplayerScreen(CChessSettings * settings , SDL_Event * event){
    int mouseX = event->button.x , mouseY = event->button.y;
    SDL_Point point = {mouseX,mouseY};
    SDL_Rect leave = {710,650,500,100};
    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT){
        if(SDL_PointInRect(&point,&leave)) settings->screenAtual = Menu;
    }
}