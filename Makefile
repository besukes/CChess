CC = gcc

CFLAGS = -Wall -ggdb -Iinclude
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

SRC = GameFiles/main.c GameFiles/initStructs.c GameFiles/afterMoves.c
OBJ = $(SRC:GameFiles/%.c=build/%.o)

TARGET = simpleSimon

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm simpleSimon
