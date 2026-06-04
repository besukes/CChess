CC = gcc

CFLAGS = -Wall -ggdb -I. -Ilibrary -Igamefiles/gameplay -Ichess_engine
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

SRC =	gamefiles/universal/corefunctions.c \
		gamefiles/gameplay/main.c \
		gamefiles/gameplay/events.c \
		gamefiles/gameplay/handleGameplay.c \
		gamefiles/gameplay/userinterface.c	\
		gamefiles/gameplay/moveMaker.c \
		gamefiles/initialization/startAndCleanup.c \
		gamefiles/initialization/initStructs.c \
		gamefiles/initialization/initTabuleiro.c \
		library/loadAssets.c \
		chess_engine/possibleMoves.c \
		chess_engine/checkAndCheckmate.c

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
