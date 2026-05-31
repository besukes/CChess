CC = gcc

CFLAGS = -Wall -ggdb -Iinclude
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

SRC1 = gamefiles/actionbased/affectedPositions.c gamefiles/actionbased/corefunctions.c
SRC2 = gamefiles/gameplay/main.c gamefiles/gameplay/events.c gamefiles/gameplay/handleGameplay.c gamefiles/gameplay/userinterface.c
SRC3 = gamefiles/initialization/initAffectedPositions.c gamefiles/initialization/startAndCleanup.c gamefiles/initialization/initStructs.c gamefiles/initialization/initTabuleiro.c
LIB = library/loadAssets.c

OBJ1 = $(SRC1:gamefiles/actionbased%.c=build/%.o)
OBJ2 = $(SRC2:gamefiles/gameplay%.c=build/%.o)
OBJ3 = $(SRC3:gamefiles/initialization%.c=build/%.o)
OBJLIB = $(LIB:library/%.c=build/%.o)

TARGET = simpleSimon

all: $(TARGET)

$(TARGET): $(OBJ1) $(OBJ2) $(OBJ3) $(OBJLIB)
	$(CC) $^ -o $@ $(LDFLAGS)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm simpleSimon
