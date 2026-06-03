#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


typedef int Boolean; //Forma mais intuitiva de perceber quando as variáveis são usadas como valores lógicos.

/*Coordenadas cartesianas*/
typedef struct Coordenadas{
    int x;
    int y;
}Coordenadas;

/*Struct que define a posicao de uma peca no tabuleiro de xadrez usando um long 64 bit*/
typedef unsigned long long uint64_bit;

/*Enum que guarda todas as peças possíveis do jogo*/
typedef enum {
    King, //The piece is the KING
    Queen, //The piece is the QUEEN
    Bishop, //The piece is the BISHOP
    Horse, //The piece is the HORSE
    Rook, //The piece is the ROOK
    Pawn, //The piece is the PAWN
    Empty //There is no piece
} Pieces;


/*Struct que guarda , para uma dada peça , as posições que ela "afeta"*/
typedef struct AffectedPositions{
    Pieces refferedPiece; //Tipo de peça que afeta as posições
    uint64_bit bitboard_position; //Posição original da peça que afeta as outras posições
    uint64_bit bitboard_position; //Posições que são afetadas por esta peça
}AffectedPositions;

typedef enum casas_board{
    A1,B1,C1,D1,E1,F1,G1,H1,
    A2,B2,C2,D2,E2,F2,G2,H2,
    A3,B3,C3,D3,E3,F3,G3,H3,
    A4,B4,C4,D4,E4,F4,G4,H4,
    A5,B5,C5,D5,E5,F5,G5,H5,
    A6,B6,C6,D6,E6,F6,G6,H6,
    A7,B7,C7,D7,E7,F7,G7,H7,
    A8,B8,C8,D8,E8,F8,G8,H8
} casas_board;

//Representa a cor de uma dada peça
typedef enum { brancas , pretas } CorPiece;

/*Este struct define uma peça com um dado tipo , uma posição própria , uma cor e um bool que informa se já se 
moveu alguma vez ou não*/
typedef struct PecaTabuleiro{
    uint64_bit bitboard_position; //Posicao na matriz de uma dada peca
    Boolean firstTimeMoving; //Informa se a peça já se moveu ou não (é relevante para algumas peças)
}PecaTabuleiro;

/*Struct que define um estado de um jogo de xadrez.
Guarda as posições de todas as peças , bem como as posições afetadas por elas.
Guarda também informações sobre se um dado king está em check/checkmate ou não*/
typedef struct EstadoJogo{
    int checkMate; //Informa se um rei está em checkmate (game over)
    int checkBrancas; //Informa se o rei branco está em check
    int checkPretas; //Informa se o rei preto está em check
    PecaTabuleiro tabuleirojogo[2][6]; //Guarda as informações do tabuleiro
    uint64_bit bitboard_brancas;
    uint64_bit bitboard_pretas;
    uint64_bit bitboard_todas_pieces;
}EstadoJogo;


typedef enum { Menu , Chess , Theme , WinScreen} UserScreen; //Define em qual tela está o utilizador


typedef enum { Invalid , Leave , Valid , Win , TooLarge} TipoJogada; //Define o tipo de jogada que o utilizador efetuou


typedef enum { CChess , ChessDotCom , LiChess} Themes; //Define o tema de peças que o utilizador está a utilizar

/*Struct que guarda o estado do jogo , tal como o turno do jogador , a peça que está a ser segurada(caso esteja a ser premida a tecla ,
que é da responsabilidade do bool isKeyPressedDown) e também a jogada do utilizador */
typedef struct GameStruct{
    EstadoJogo estadoJogo; //Estado atual do jogo
    Boolean isKeyPressedDown; //Verifica se o utilizador está a premir a tecla
    Pieces pieceSelecionada; //Guarda a peça que o utilizador está a ser segurada , caso esteja
    uint64_bit pieceCoords; //Guarda a posição de onde a peça que está a ser segurada veio , caso esteja
    CorPiece turnoJogador; //Guarda o turno do utilizador 
    TipoJogada jogada; //Guarda a jogada do utilizador
}GameStruct;


/*Guarda as texturas que o jogo utiliza no seu decorrer , tal como o tema das peças*/
typedef struct AssetsCChess{
    Themes temaSelecionado; //Tema selecionado pelo utilizador
    SDL_Texture * chessPieces[12]; //Texturas das peças de xadrez do CChess
    SDL_Texture * tabTextures[2]; //Texturas dos tabuleiros de xadrez do CChess
    SDL_Texture * miscTextures[20]; //Texturas misc do CChess
}AssetsCChess;

/*Struct que guarda as definições do jogo CChess mais relevantes , como o renderer responsável para apresentar imagens,
as texturas do jogo , a fonte das letras do jogo , as posições verticais e horizontais do rato do utilizador , o nª de ticks
que já se passaram deste o começo do jogo , bem como a tela em que o utilizador se encontra*/
typedef struct CChessSettings{
    AssetsCChess textures; //Texturas do jogo CChess
    SDL_Renderer * gameRenderer; //Renderer responsável por guardar a janela e onde desenhamos os objetos
    TTF_Font * fonteJogo; //Fonte das letras do nosso jogo
    int posMouseX; //Posição horizontal do rato do utilizador , em termos de píxeis
    int posMouseY; //Posição vertical do rato do utilizador , em termos de píxeis
    UserScreen screenAtual; //Tela atual em que o utilizador se encontra
    int ticks; //Número de ticks que já passaram desde o começo do jogo (importante para o timer)
}CChessSettings;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////     MODULOS     ///////////////////////////////////////////////////////////////////////////

//Modulo initStructs.c

EstadoJogo initEstadoJogo(void);
CChessSettings initCChessSettings(SDL_Renderer * sdl_renderer);
GameStruct initGameStruct(SDL_Renderer * sdl_renderer);



//Modulo afterMoves.c

AffectedPositions * initPosicoesAfetadas(int additor);




//Modulo initTabuleiro.c

PecaTabuleiro * initTabuleiro(PecaTabuleiro pt[32],int additor);




//Modulo loadAssets.c

void initTexturasJogo(AssetsCChess * assets,SDL_Texture * sdl_renderer);


//Modulo handleGameplay.c
void handleJogadaMenuPrincipal(CChessSettings * settings,SDL_Event event);
void handleJogadaChess(GameStruct* game , CChessSettings * settings,SDL_Event event);
void handleJogadaThemes(CChessSettings * settings,SDL_Event event);
void handleWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event);



//Modulo startAndCleanup.c

SDL_Renderer * sdl_initializer(void);
void free_allocated_memory(GameStruct game , CChessSettings user);