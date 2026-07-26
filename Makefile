CC = gcc

CFLAGS = -Wall -ggdb -Wextra -g3 -fsanitize=address,undefined -I. -Ilibrary 
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_gfx -lm -fsanitize=address,undefined

SRC =	src/universal/corefunctions.c \
		src/universal/chess_important.c \
		src/universal/animations.c \
		src/gameplay/interfacelogic/main.c \
		src/gameplay/interfacelogic/events.c \
		src/gameplay/interfacelogic/handleGameplay.c \
		src/initialization/startAndCleanup.c \
		src/initialization/initStructs.c \
		src/initialization/initTabuleiro.c \
		src/initialization/gamefiles.c \
		src/initialization/gamefiles_aux.c \
		src/initialization/storygame.c \
		src/gameplay/userinterface/universal_draws.c \
		src/gameplay/userinterface/offline.c \
		src/gameplay/userinterface/story.c \
		src/gameplay/userinterface/menu.c \
		src/gameplay/userinterface/themes.c \
		src/gameplay/userinterface/win_screen.c \
		src/gameplay/userinterface/settings.c \
		src/multiplayer/multiplayer_logic.c \
		src/multiplayer/multiplayerUI.c \
		library/loadAssets.c \
		chess_engine/chess_logic/possibleMoves.c \
		chess_engine/chess_logic/checkAndCheckmate.c \
		chess_engine/chess_logic/en_passant.c \
		chess_engine/chess_logic/moveMaker.c \
		chess_engine/chess_logic/undoMove.c \
		chess_engine/chess_logic/castle_logic.c \
		chess_engine/chess_logic/custom_interactions.c \
		chess_engine/chess_bot/engine.c \
		chess_engine/chess_bot/evaluation.c \
		chess_engine/chess_bot/search.c \

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
	@pkg-config --exists SDL2_gfx || { echo "SDL2_gfx missing"; exit 1; }
	@test -f /usr/include/dirent.h || { echo "dirent.h missing (Non-POSIX system?)"; exit 1; }

	@echo "All dependencies OK"
