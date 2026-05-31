
typedef int Boolean;

typedef struct Coordenadas{
    int linha;
    int coluna;
}Coordenadas;

//Enum que guarda todas as peças do jogo
typedef enum {
    King, //The piece is the KING
    Queen, //The piece is the QUEEN
    Bishop, //The piece is the BISHOP
    Horse, //The piece is the HORSE
    Rook, //The piece is the ROOK
    Pawn, //The piece is the PAWN
    Empty //There is no piece
} Pieces;


typedef struct AffectedPositions{
    Pieces refferedPiece;
    Coordenadas cordenadaPiece;
    Coordenadas * cordJogo;
}AffectedPositions;

typedef enum {
    Branca,
    Preta
}CorPiece;

typedef struct PecaTabuleiro{
    int linhaTabuleiro;
    int colunaTabuleiro;
    CorPiece cor;
    Pieces tipoPiece;
    Boolean firstTimeMoving;
}PecaTabuleiro;


typedef struct EstadoJogo{
    int checkMate;
    int checkBrancas;
    int checkPretas;
    PecaTabuleiro tabuleiroJogoBrancas[16];
    PecaTabuleiro tabuleiroJogoPretas[16];
    int maxIndxBrancas;
    int maxIndxMemoriaB;
    AffectedPositions * posicoesAfetadasBrancas;
    int maxIndxPretas;
    int maxIndxMemoriaP;
    AffectedPositions * posicoesAfetadasPretas;
}EstadoJogo;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////     MODULOS     ///////////////////////////////////////////////////////////////////////////

//Modulo initStructs.c

EstadoJogo initEstadoJogo(void);


//Modulo afterMoves.c

AffectedPositions * initPosicoesAfetadas(int additor);


//Modulo initTabuleiro.c

PecaTabuleiro * initTabuleiro(PecaTabuleiro pt[32],int additor);
