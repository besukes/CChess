#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

/*Struct que serve apenas no startAndCleanup.c para retornar os endereços de memória do nosso renderer e window*/
typedef struct SDL_Initializators{
    SDL_Renderer * renderer; //renderer do jogo
    SDL_Window * window; //window do jogo
}SDL_Initializators;

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
    Pawn, //The piece is a PAWN
    Rook, //The piece is the ROOK
    Horse, //The piece is the HORSE
    Bishop, //The piece is the BISHOP
    Queen, //The piece is the QUEEN
    King, //The piece is the KING
    TheDog, //CChess Dog piece that protects the 3 squares in front of him (Norte , Nordeste , Noroeste)
    Empty, //There is no piece
} Pieces;

/*Bitboard que cada indice representa o numero de left shifts que temos de fazer para chegar a essa posição no tabuleiro */
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

//Representa os diferentes castle types
typedef enum { Short , Long } CastleTypes;

//Representa uma peça extra do jogo CChess no tabuleiro
typedef struct ExtraPieces{
    Pieces tipo_piece; //Tipo de extra piece do tabuleiro do jogo
    CorPiece cor_piece; //Cor da extra piece do tabuleiro do jogo
    uint64_bit bitboard_extra_piece; //Posicao desta extra piece no jogo
}ExtraPieces;

//A memória da ordem das peças que o utilizador utiliza no jogo estará guardada como um par (TipoPiece,PosPiece)
typedef ExtraPieces PlayerChessTable;

/*Struct que define um estado de um jogo de xadrez.
Guarda as posições de todas as peças , bem como as posições afetadas por elas.
Guarda também informações sobre se um dado king está em check/checkmate ou não*/
typedef struct EstadoJogo{
    int checkMate; //Informa se um rei está em checkmate (game over)
    int stalemate; //Informa se o jogo acabou em staleMate
    int king_in_check[2]; //Informa se o reis estão em check
    int canCastle[2][2]; //Matriz de possibilidades de dar castle
    uint64_bit enpassant; //Guarda a posição possível de se fazer enpassant
    uint64_bit tabuleirojogo[2][6]; //Guarda as informações do tabuleiro das peças regulares de xadrez
    int indx_extra_pieces; //Guarda o número de extra pieces presentes no jogo atual
    ExtraPieces * tabuleiroExtraPieces; //Guarda as informações do tabuleiro das peças extras do CChess
    uint64_bit bitboard_brancas; // Bitboard das peças brancas
    uint64_bit bitboard_pretas; // Bitboard das peças pretas
    uint64_bit bitboard_todas_pieces; //Bitboard que guarda as posições ocupadas por todas as peças no jogo
}EstadoJogo;

typedef enum { Menu , Chess , Story , Theme , WinScreen , DrawScreen , Settings , Multiplayer} UserScreen; //Define em qual tela está o utilizador

typedef enum { Invalid , Leave , Valid , Checkmate , TooLarge , Stalemate} TipoJogada; //Define o tipo de jogada que o utilizador efetuou

typedef enum { CChess , ChessDotCom , LiChess} Themes; //Define o tema de peças que o utilizador está a utilizar

//Define o nível de dificuldade do jogo (para o modo singleplayer , que ainda não existe)
typedef enum { Floresta , Caminhos , Montanha , Castelo , Mar , Deserto , Vulcao , CidadeSimples , CidadeScifi , Espaco} Niveis;

/*Linked List que guarda a piece que foi comida na jogada anterior , para depois desfazer a jogada , caso seja necessário*/
typedef struct PecasComidas{
    uint64_bit pos_de_piece;
    Pieces tipo_piece;
    CorPiece cor_piece;
    struct PecasComidas * prox;
} * PecasComidasLL;

/*Guarda informações sobre os tutoriais já realizados pelo utilizador no jogo*/
typedef struct TutorialsDone{
    Boolean tutorial_offline_done; //Informa se já realizou o tutorial do modo offline
    Boolean tutorial_story_done; //Informa se já realizou o tutorial do modo história
    Boolean tutorial_multiplayer_done; //Informa se já realizou o tutorial do modo multiplayer
}TutorialsDone;

/*Define o tipo de ultimates/poderes que existem no jogo*/
typedef enum {None , FieryQueen , JumpingHorse , FearlessPawn , THEROOK , HolyGrace , 
              GeekKing , TimeTravelerKing , MistyKnight
             } TypeUltimate;

/*Struct responsável por guardar os poderes de cada piece*/
typedef struct UltimatesSettings{
    Pieces ultimate_refers_piece; //Define a piece respectiva desta ultimate
    TypeUltimate ultimate; //Define o power up da piece
}UltimatesSettings;

/*Struct responsável por guardar os poderes de cada piece*/
typedef struct Ultimates{
    Boolean * power_on; //Define se o poder está ativado nesse turno , ou não , para cada respectiva piece
    TypeUltimate ultimate; //Define o poder da piece atual , para cada piece
}Ultimates;

/*Struct responsável por guardar as informações da última ultimate usada*/
typedef struct UltimatesActive{
    TypeUltimate ultimate_used; //Define o tipo de ultimate Usada (só pode ser tipos que afetam o tabuleiro em vários turnos)
    int turns_duration; //Define o tempo que esta ultimate vai durar no tabuleiro
    uint64_bit ult_affected_positions; //Define as posições afetadas pela ultimate , no tabuleiro
}UltimatesActive;


/*Struct que guarda o estado do jogo , tal como o turno do jogador , a peça que está a ser segurada(caso esteja a ser premida a tecla ,
que é da responsabilidade do bool isKeyPressedDown) e também a jogada do utilizador */
typedef struct GameStruct{
    Boolean game_needs_initialization; //Indica se o jogo precisa ser inicializado consoante a tela do utilizador
    EstadoJogo estadoJogo; //Estado atual do jogo
    Ultimates pieces_power[2][6]; //Guarda os poderes selecionados de cada piece do xadrez original
    Ultimates extra_pieces_power[2][6]; //Guarda os poderes selecionados de cada piece extra do CChess
    UltimatesActive * active_ultimate; //Guarda as ultimates que estão ativadas neste momento no tabuleiro
    Boolean isKeyPressedDown; //Verifica se o utilizador está a premir a tecla
    Pieces pieceSelecionada; //Guarda a peça que o utilizador está a ser segurada , caso esteja
    uint64_bit pieceCoords; //Guarda a posição de onde a peça que está a ser segurada veio , caso esteja
    uint64_bit selected_piece_attacks; //Guarda as posições da peça que estão sobre ataque da mesma
    CorPiece turnoJogador; //Guarda o turno do utilizador 
    TipoJogada jogada; //Guarda a jogada do utilizador
    PecasComidasLL lastmoves; //Guarda a peça que foi comida na jogada anterior , para depois desfazer a jogada , caso seja necessário
    Boolean pawnPromoted; //Guarda se o peão está a ser promovido
    Boolean promotedSucessfully; //Guarda se o peão foi promovido num clique
}GameStruct;


/*Struct que guarda as escolhas de cosméticos do utilizador*/
typedef struct InGame_Cosmetics{
    int tabuleiroSelecionado; //Tabuleiro selecionado pelo utilizador
    int musicaSelecionada; //Música selecionada pelo utilizador
    int efeito_checkmateSelecionado; //Efeito de checkmate selecionado pelo utilizador
    SDL_Texture * * gif_checkmate; //Texturas da animação de checkmate selecionada pelo utilizador
    int efeito_checkSelecionado; //Efeito de check selecionado pelo utilizador
}InGame_Cosmetics;

/*Guarda as texturas que o jogo utiliza no seu decorrer , tal como o tema das peças*/
typedef struct AssetsCChess{
    Themes temaSelecionado; //Tema selecionado pelo utilizador
    SDL_Texture * chessPieces[12]; //Texturas das peças de xadrez do CChess
    SDL_Texture * tabTextures[5]; //Texturas dos tabuleiros de xadrez do CChess
    SDL_Texture * niveisTextures[10]; //Texturas misc do CChess
    SDL_Texture * buttonsTextures[20]; //Texturas dos botões do CChess
    SDL_Texture * miscTextures[20]; //Texturas misc do CChess
}AssetsCChess;

/*Struct responsável por guardar as informações do utilizador sobre peças personalizadas e poderes do CChess*/
typedef struct CustomPieces{
    int indx_ult_unlocked; //index para o array dinamicamente alocado
    TypeUltimate * ultimates_unlocked; //Poderes que o utilizador possui desbloqueados para comprar
    int indx_ult_owned; //index para o array dinamicamente alocado
    TypeUltimate * ultimates_owned; //Poderes que o utilizador possui comprados]
    int indx_ep_owned; //index para o array dinamicamente alocado
    Pieces * extraPieces_owned; //Pieces personalizadas que o utilizador compradas
}CustomPieces;

/*Struct que guarda as definições do jogo CChess mais relevantes , como o renderer responsável para apresentar imagens,
as texturas do jogo , a fonte das letras do jogo , as posições verticais e horizontais do rato do utilizador , o nª de ticks
que já se passaram deste o começo do jogo , bem como a tela em que o utilizador se encontra*/
typedef struct CChessSettings{
    AssetsCChess textures; //Texturas do jogo CChess
    SDL_Renderer * gameRenderer; //Renderer responsável por guardar a janela e onde desenhamos os objetos
    SDL_Window * window; //Window atual do utilizador
    TTF_Font * fonteJogo; //Fonte das letras do nosso jogo
    int posMouseX; //Posição horizontal do rato do utilizador , em termos de píxeis
    int posMouseY; //Posição vertical do rato do utilizador , em termos de píxeis
    UserScreen screenAtual; //Tela atual em que o utilizador se encontra
    int ticks; //Número de ticks que já passaram desde o começo do jogo (importante para o timer)
    int ticks_checkmate; //Número de ticks que já passaram desde o começo da animação de checkmate (importante para o timer)
    Niveis nivelDificuldade; //Nível de dificuldade do jogo (para o modo carreira , que ainda não existe)
    int nivelSelecionado; //Nível selecionado para cada fase do jogo
    InGame_Cosmetics cosmeticos; //Guarda as escolhas de cosméticos do utilizador (para o modo singleplayer , que ainda não existe)
    int num_imgsLoaded; //Número de imagens já carregadas ao inicializar o programa
    int num_imgsTotais; //Número de imagens totais que necessitam ser carregadas
    CustomPieces user_custom_items; //Struct que guarda as informações do utilizador quanto a items personalizados
    int ccoins_qntd; //Guarda a quantidade de moedas do utilizador
    int indx_starting_line; //index para o array dinamicamente alocado
    PlayerChessTable * story_st_line; //Guarda a informação do utilizador quanto à organização das peças no modo história
    int indx_selected_ults; //index para o array dinamicamente alocado
    UltimatesSettings * selected_pieces_power; //Guarda os poderes selecionados de cada piece
    TutorialsDone tutorials; //Guarda booleans que informam sobre o estado do utilizador quanto aos tutoriais de cada modo de jogo
}CChessSettings;


typedef uint64_bit (*ShiftFunction)(uint64_bit,int);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////     MODULOS     ///////////////////////////////////////////////////////////////////////////


//Modulo initStructs.c

CChessSettings initCChessSettings(SDL_Renderer * sdl_renderer , SDL_Window * window);
GameStruct initGameStruct(SDL_Renderer * sdl_renderer);
EstadoJogo initEstadoJogo(void);
void initializeOfflineGame(GameStruct * game);




//Modulo initTabuleiro.c

void initTabuleiro(uint64_bit pt[6], int additor);
void init_other_bitboards(EstadoJogo * es);




//Modulo loadAssets.c

void initTexturasJogo(CChessSettings * settings , AssetsCChess * assets,SDL_Renderer * sdl_renderer);




//Modulo handleGameplay.c
void handleJogadaMenuPrincipal(CChessSettings * settings,SDL_Event * event);
void handleJogadaChess(GameStruct* game , CChessSettings * settings,SDL_Event event);
void handleJogadaThemes(CChessSettings * settings,SDL_Event event);
void handleWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event);
void handleStoryScreen(GameStruct* game , CChessSettings * settings,SDL_Event * event);
void handleJogadaStory(GameStruct* game , CChessSettings * settings,SDL_Event event);



//Modulo startAndCleanup.c

SDL_Initializators sdl_initializer(void);
void free_allocated_memory(GameStruct * game , CChessSettings * user);




//Modulo corefunctions.c

int posTabuleiro(uint64_bit bitboard);
uint64_bit click_table_position(int mouseX , int mouseY);
int dentroDoBotao(int mx , int my , int inf_x , int sup_x , int inf_y , int sup_y);
int minimum(int n1,int n2);
Pieces comparePiece(EstadoJogo estado , CorPiece cor , uint64_bit posclique);
void addHeadLinkedList(PecasComidasLL * list , Pieces piece_comida , uint64_bit pos_piece , CorPiece cor);
void freeLinkedList(PecasComidasLL list);
void getColunasAH(uint64_bit * colunaA , uint64_bit * colunaH);
int strToNumber(char * str);
char * skipWhileSpace(char * str);
int compareString(char comparing[],char compared[]);
int numberChars(char * str);
char * skip_to_value(char * line);
int get_number(char * line, int max , int def);




//Modulo events.c

void efetuaEventoClique(GameStruct * game , CChessSettings * settings,SDL_Event * event);
void efetuaEventoSoltar(GameStruct * game , CChessSettings * settings , SDL_Event event);
void efetuaEventoClickStory(GameStruct * game , CChessSettings * settings,SDL_Event * event, Boolean valido_turno);




//Modulo moveMaker.c

void atualizaJogada(GameStruct * game , uint64_bit click,Boolean castles,Boolean enpassant);
void updateBitboard_ClickEvent(CorPiece turno,Pieces piece,EstadoJogo * estado,uint64_bit click);
int clickPromotingPiece(GameStruct * game , int mouseX , int mouseY);




//Modulo possibleMoves.c

int isPseudoValidMove(GameStruct * game , uint64_bit drop,Boolean * castle,Boolean * enpassant , Boolean * promote);
uint64_bit get_knight_attacks(uint64_bit piece_pos);
uint64_bit get_pawn_attacks(uint64_bit piece_pos,CorPiece cor);
uint64_bit get_sliding_attacks(uint64_bit piece_pos, uint64_bit pos_limites);
uint64_bit get_cross_attacks(uint64_bit piece_pos , uint64_bit pos_limites);
uint64_bit get_piece_attacks(uint64_bit pos,Pieces piece,GameStruct * game,CorPiece cor_turno);
uint64_bit get_king_moves(uint64_bit pos);
uint64_bit get_dog_protected_squares(uint64_bit pos_dog ,CorPiece turno);




//Modulo userinterface.c

void desenhaInterfaceMenu(CChessSettings * settings,SDL_Event event);
void desenhaInterfaceJogo(GameStruct * game ,CChessSettings * settings,SDL_Event event);
void desenhaMenuThemes(CChessSettings * settings,SDL_Event event);
void desenhaWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event);
void desenharPieceDrag(Pieces tipoPiece , int mouseX , int mouseY , CChessSettings * settings , int offset);




//Modulo checkAndCheckmate.c

TipoJogada check_or_mate(GameStruct * game, Boolean castles , uint64_bit click);
int isCheckMate(GameStruct * game, CorPiece cor);
void notInCheck(GameStruct * game);
Boolean is_in_check(EstadoJogo * estado , uint64_bit kingpos , CorPiece cor);





//Modulo en_passant.c

void update_en_passant(GameStruct * game);
Boolean can_en_passant(GameStruct * game , uint64_bit drop,CorPiece cor);
void enpassant_move(GameStruct * game , uint64_bit * cor_oposta , uint64_bit * mesma_cor,ShiftFunction ep);





//Modulo chess_important.c

int pawnFirstRank(uint64_bit pos,CorPiece cor);
uint64_bit shiftr(uint64_bit pos,int shift);
uint64_bit shiftl(uint64_bit pos,int shift);
uint64_bit get_same_colour_bitboard(EstadoJogo * estado , CorPiece cor);
uint64_bit initQuadrado(void);
uint64_bit get_opposing_colour_bitboard(EstadoJogo * estado , CorPiece cor);
uint64_bit get_selected_piece_attacks(GameStruct * game , CChessSettings * settings , uint64_bit click , Pieces piece , CorPiece turno);



//Modulo undoMove.c

void undoMove(GameStruct * game , uint64_bit click , Boolean castles);



//Modulo castle_logic.c

int is_castelling_king(uint64_bit pos_piece , GameStruct * game , CorPiece cor , uint64_bit drop);
int invalidCastle(GameStruct * game , uint64_bit click);
void verifica_direito_castle(GameStruct * game ,CorPiece turno);
void castle_King(GameStruct * game , uint64_bit click , int square, uint64_bit * mesmaCor);




//Modulo universal_draws.c

void desenharPiece(Pieces tipoPiece , int linha , int coluna , CChessSettings * settings, int offset);
void desenhaTipoPiece(uint64_bit pos_pieces,Pieces tipoPiece , CChessSettings * settings, GameStruct * game, int offset);
void desenharPieceDrag(Pieces tipoPiece , int mouseX , int mouseY , CChessSettings * settings , int offset);
void desenharPieceAttacks(CChessSettings * settings , uint64_bit passant , uint64_bit attacks , uint64_bit cor_oposta);
void desenhaCheck(GameStruct * game , CChessSettings * settings);



//Modulo game_screen.c

void desenhaInterfaceJogo(GameStruct * game ,CChessSettings * settings,SDL_Event event);





//Modulo menu.c

void desenhaInterfaceMenu(CChessSettings * settings,SDL_Event event);




//Modulo themes.c

void desenhaMenuThemes(CChessSettings * settings,SDL_Event event);



//Modulo win_screen.c

void desenhaWinScreen(GameStruct * game ,CChessSettings * settings,SDL_Event event);


//Modulo animations.c

SDL_Texture ** gif_utilizador_checkmate(CChessSettings * settings, int efeito_checkmateSelecionado);
void loading_screen(CChessSettings * settings,int perc);



//Modulo gamefiles.c

void initGameFiles(CChessSettings * settings);
void writeNewGameFiles(CChessSettings * settings);


//Modulo custom_interactions.c 

int is_protected_square(GameStruct * game , uint64_bit click);


//Modulo story.c

void desenhaStoryScreen(GameStruct * game,CChessSettings * settings);


//Modulo storylogic.c

void initStoryGame(GameStruct * game , CChessSettings * settings , int level);