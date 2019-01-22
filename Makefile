CC = g++
CFLAGS = -Wall
SRC_PATH = sources/
OBJ_PATH = objects/
BIN_PATH = bin/
EXEC_NAME = jeu
LIBS = -lSDL2 -lSDL2_image
OBJ_FILES = Voiture.o main.o Artefact.o Bonus.o Vie.o Cailloux.o Malus.o Trou.o Piece.o Jeu.o

all : outDirs $(addprefix $(BIN_PATH), $(EXEC_NAME))

outDirs:
	mkdir -p $(OBJ_PATH)
	mkdir -p $(BIN_PATH)

clean :
	rm $(addprefix $(BIN_PATH), $(EXEC_NAME)) $(addprefix $(OBJ_PATH), $(OBJ_FILES))
	rm -r $(OBJ_PATH)
	rm -r $(BIN_PATH)

$(addprefix $(BIN_PATH), $(EXEC_NAME)) : $(addprefix $(OBJ_PATH), $(OBJ_FILES))
	$(CC) $(CFLAGS) -o $(addprefix $(BIN_PATH), $(EXEC_NAME)) $(addprefix $(OBJ_PATH), $(OBJ_FILES)) $(LIBS)

$(addprefix $(OBJ_PATH), %.o): $(addprefix $(SRC_PATH), %.cc)
	$(CC) $(CFLAGS) -o $@ -c $<

$(addprefix $(OBJ_PATH), %.o): $(addprefix $(SRC_PATH), %.cc) $(addprefix $(SRC_PATH), %.hh)
	$(CC) $(CFLAGS) -o $@ -c $<
