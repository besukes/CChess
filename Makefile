CC = gcc

CFLAGS = -Wall -ggdb -I. -Ilibrary -Igamefiles/gameplay
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

SRC = gamefiles/actionbased/affectedPositionsCalc.c \
		gamefiles/actionbased/corefunctions.c \
		gamefiles/gameplay/main.c \
		gamefiles/gameplay/events.c \
		gamefiles/gameplay/handleGameplay.c \
		gamefiles/gameplay/userinterface.c	\
		gamefiles/initialization/initAffectedMoves.c \
		gamefiles/initialization/startAndCleanup.c \
		gamefiles/initialization/initStructs.c \
		gamefiles/initialization/initTabuleiro.c \
		library/loadAssets.c

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
