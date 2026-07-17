#include "library/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>



void efetuaEventoClickArrows(GameStruct * game , SDL_Event event){
    game->arrows.is_drawing_arrows = 1;
    int indx = ++ game->arrows.indx_drawable_arrows;
    game->arrows.arrows_vector = realloc(game->arrows.arrows_vector,sizeof(Coordenadas[2])*indx);
    int (*vector)[2] = game->arrows.arrows_vector + indx - 1;
    uint64_bit table_pos = click_table_position(event.button.x,event.button.y);
    int pos = posTabuleiro(table_pos); //verifica se table_pos == 0 , se nao retorna a posicao de 0-63
    if(pos!= (-1)) (*vector)[0] = pos;
}


void efetuaEventoSoltarArrows(GameStruct * game , SDL_Event event){
    game->arrows.is_drawing_arrows = 0;
    int * indx = &game->arrows.indx_drawable_arrows;
    int (*vector)[2] = game->arrows.arrows_vector + *indx - 1;
    uint64_bit table_pos = click_table_position(event.button.x,event.button.y);
    int pos_nova = posTabuleiro(table_pos) , //verifica se table_pos == 0 , se nao retorna a posicao de 0-63
        pos_ant = (*vector)[0];
    if(pos_nova!= (-1) && pos_nova != pos_ant) (*vector)[1] = pos_nova;
    else{
        (*indx)--;
        if(!(*indx)){
            free(game->arrows.arrows_vector);
            game->arrows.arrows_vector = NULL;
        }
        else game->arrows.arrows_vector = realloc(game->arrows.arrows_vector,sizeof(Coordenadas[2])*(*indx));\
    }
}





int clickPromotingPiece(GameStruct * game , int mouseX , int mouseY){
    int ret = 1 , mult = (game->turnoJogador == brancas) ? 1 : (-1);
    game->promoted.pawnPromoted = 0;
    uint64_bit promotion_square = game->promoted.promoted_square;
    int tamSquareX = 110;
    int offsetY = ( (posTabuleiro(promotion_square) / 8 ) < 1) ? 800 : 0;
    int offsetX = posTabuleiro(promotion_square)%8;
    if(dentroDoBotao(mouseX,mouseY,255 + tamSquareX*offsetX,345 + tamSquareX*offsetX,105 + offsetY,192 + offsetY)){ //Queen
        promotePiece(game,Queen,promotion_square);
        game->score_game += 8*mult;
    }
    else if(dentroDoBotao(mouseX,mouseY,345 + tamSquareX*offsetX,425 + tamSquareX*offsetX,105 + offsetY,192 + offsetY)){ //Rook
        promotePiece(game,Rook,promotion_square);
        game->score_game += 5*mult;
    }
    else if(dentroDoBotao(mouseX,mouseY,255 + tamSquareX*offsetX,345 + tamSquareX*offsetX,187 + offsetY,275 + offsetY)){ //Bishop
        promotePiece(game,Bishop,promotion_square);
        game->score_game += 3*mult;
    }
    else if(dentroDoBotao(mouseX,mouseY,345 + tamSquareX*offsetX,425 + tamSquareX*offsetX,187 + offsetY,275 + offsetY)){ //Knight
        promotePiece(game,Horse,promotion_square);
        game->score_game += 3*mult;
    }
    else{//Invalid click
        game->promoted.pawnPromoted = 1;
        ret = 0;
    }
    return ret;
}



void efetuaEventoClique(GameStruct * game , CChessSettings * settings,SDL_Event * event){
    int mouseX = event->button.x , mouseY = event->button.y;
    uint64_bit click = click_table_position(mouseX,mouseY);
    int * is_leaving = &game->trying_to_leave;
    if(game->promoted.pawnPromoted && !*is_leaving){
        int did_promote = clickPromotingPiece(game,mouseX,mouseY);
        if(did_promote){
            game->promoted.promotedSucessfully = 1;
            game->promoted.promoted_square = 0;
        }
    }
    else if(click != 0 && !*is_leaving){
        Pieces piece = comparePiece(game->estadoJogo ,game->turnoJogador, click);
        game->pieceCoords = click;
        game->pieceSelecionada = piece;
        if(piece==Empty) game->jogada = Invalid;
        CorPiece turno = game->turnoJogador;
        game->selected_piece_attacks = get_selected_piece_attacks(game,click,piece,turno);
    }
    else{
        SDL_Point point = {mouseX,mouseY};
        SDL_Rect returns = {1425,950,202,100};
        SDL_Rect back = {765,570,180,86} , stay = {975,570,180,86};
        if(SDL_PointInRect(&point,&returns) && !*is_leaving) *is_leaving = 1;
        else if(*is_leaving){
            if(SDL_PointInRect(&point,&back)){
                settings->screenAtual = Menu;
                game->game_needs_initialization = 1;
            }
            else if(SDL_PointInRect(&point,&stay)) *is_leaving = 0;
        }
        else if(1){
            
        }
    }
}



void eventoFimJogo(CChessSettings * settings, UserScreen screen){
    settings->screenAtual = screen;
    settings->ticks_checkmate = settings->ticks;
}



void eventoPromotePiece(GameStruct * game , CChessSettings * settings,uint64_bit click){
    game->jogada = check_move(game,0,click);
    game->promoted.promotedSucessfully = 0;
    if(game->jogada == Checkmate) eventoFimJogo(settings,WinScreen);
    else if(game->jogada == Stalemate) eventoFimJogo(settings,DrawScreen);
    else if(game->jogada == Invalid) game->jogada = Valid; //Apenas para prevenir bugs
}



void updateScore(GameStruct *game){
    if(game->lastmoves!=NULL){
        Pieces p = game->lastmoves->tipo_piece;
        int mult = 1;
        if(game->lastmoves->cor_piece == brancas) mult = (-1);
        switch(p){
            case 0:
                game->score_game+=1*mult;
            break;
            case 1:
                game->score_game+=5*mult;
            break;
            case 2:
                game->score_game+=3*mult;
            break;
            case 3:
                game->score_game+=3*mult;
            break;
            case 4:
                game->score_game+=8*mult;
            break;
            case 6:
                game->score_game+=4*mult;
            break;
            default:break;
        }
    }
}


void freePiecesTaken(GameStruct * game){
    if(game->lastmoves != NULL) freeLinkedList(game->lastmoves);
    game->lastmoves = NULL;
}



void efetuaEventoSoltar(GameStruct * game , CChessSettings * settings , SDL_Event event){
    int mouseX = event.button.x , mouseY = event.button.y;
    Boolean castles = 0, enpassant = 0 , promote = 0;
    uint64_bit click = click_table_position(mouseX,mouseY);
    if(game->promoted.promotedSucessfully) eventoPromotePiece(game,settings,click);
    else if(click != 0 && isPseudoValidMove(game,click,&castles,&enpassant,&promote) && !game->promoted.pawnPromoted){
            int check_antes = game->estadoJogo.king_in_check[game->turnoJogador];
            atualizaJogada(game,click,castles,enpassant);
            game->jogada = check_move(game,castles,click);
            if(game->jogada==Invalid){
                undoMove(game,click,castles);
                game->estadoJogo.king_in_check[game->turnoJogador] = check_antes;
            }
            else if(game->jogada == Checkmate) eventoFimJogo(settings,WinScreen);
            else if(game->jogada == Stalemate) eventoFimJogo(settings,DrawScreen);
            else {
                notInCheck(game);
                update_en_passant(game,click);
                game->promoted.pawnPromoted = promote;
                if(promote) game->promoted.promoted_square = click; //para depois se desenhar o quadrado de promoção na posição correta
                else updateScore(game);
            }
    }
    else{
        game->jogada = Invalid;
    }
    game->selected_piece_attacks = 0;
    freePiecesTaken(game);
}



void efetuaEventoClickStory(GameStruct * game , CChessSettings * settings,SDL_Event * event, Boolean valido_turno){
    int mouseX = event->button.x , mouseY = event->button.y;
    uint64_bit click = click_table_position(mouseX,mouseY);
    if(!valido_turno || (click == 0) ){
        SDL_Point point = {mouseX,mouseY};
        SDL_Rect leave = {50,950,100,100};
        if(SDL_PointInRect(&point,&leave)){ 
            settings->screenAtual = Menu;
            game->game_needs_initialization = 1;
        }
        else if(1){
            
        }
    }
    else{
        if(game->promoted.pawnPromoted){
            int did_promote = clickPromotingPiece(game,mouseX,mouseY);
            if(did_promote) game->promoted.promotedSucessfully = 1;
        }
        else{
            Pieces piece = comparePiece(game->estadoJogo ,game->turnoJogador, click);
            game->pieceCoords = click;
            game->pieceSelecionada = piece;
            if(piece==Empty) game->jogada = Invalid;
        }
    }
}



void cleanArrowEvent(GameStruct * game){
    ArrowsGame * arrows = &game->arrows;
    arrows->is_drawing_arrows = 0;
    arrows->indx_drawable_arrows = 0;
    free(arrows->arrows_vector);
    arrows->arrows_vector = NULL;
}