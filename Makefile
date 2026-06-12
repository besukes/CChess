CC = gcc

CFLAGS = -Wall -ggdb -I. -Ilibrary -Igamefiles/gameplay -Ichess_engine
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

SRC =	gamefiles/universal/corefunctions.c \
		gamefiles/universal/chess_important.c \
		gamefiles/universal/animations.c \
		gamefiles/gameplay/interfacelogic/main.c \
		gamefiles/gameplay/interfacelogic/events.c \
		gamefiles/gameplay/interfacelogic/handleGameplay.c \
		gamefiles/initialization/startAndCleanup.c \
		gamefiles/initialization/initStructs.c \
		gamefiles/initialization/initTabuleiro.c \
		gamefiles/gameplay/userinterface/draw_pieces.c \
		gamefiles/gameplay/userinterface/game_screen.c \
		gamefiles/gameplay/userinterface/menu.c \
		gamefiles/gameplay/userinterface/themes.c \
		gamefiles/gameplay/userinterface/win_screen.c \
		library/loadAssets.c \
		chess_engine/possibleMoves.c \
		chess_engine/checkAndCheckmate.c \
		chess_engine/en_passant.c \
		chess_engine/moveMaker.c \
		chess_engine/undoMove.c \
		chess_engine/castle_logic.c 

OBJ = $(SRC:%.c=build/%.o)


TARGET = cchess

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm cchess

check:
	@command -v gcc >/dev/null 2>&1 || { echo "gcc not installed"; exit 1; }
	@command -v make >/dev/null 2>&1 || { echo "make not installed"; exit 1; }

	@pkg-config --exists sdl2 || { echo "SDL2 missing"; exit 1; }
	@pkg-config --exists SDL2_image || { echo "SDL2_image missing"; exit 1; }
	@pkg-config --exists SDL2_mixer || { echo "SDL2_mixer missing"; exit 1; }
	@pkg-config --exists SDL2_ttf || { echo "SDL2_ttf missing"; exit 1; }

	@echo "All dependencies OK"
