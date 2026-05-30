
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
    int quantidadePecasJogo;
    PecaTabuleiro tabuleiroJogo[32];
    int maxIndxBrancas;
    AffectedPositions * posicoesAfetadasBrancas;
    int maxIndxPretas;
    AffectedPositions * posicoesAfetadasPretas;
}EstadoJogo;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////     MODULOS     ///////////////////////////////////////////////////////////////////////////

EstadoJogo initEstadoJogo(void);
