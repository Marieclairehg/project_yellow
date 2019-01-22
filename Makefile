CC = g++
CFLAGS = -Wall
SRC_PATH = sources/
OBJ_PATH = objects/
BIN_PATH = bin/
EXEC_NAME = jeu
LIBS = -lSDL2 -lSDL2_image
OBJ_FILES = Voiture.o main.o Artefact.o Bonus.o Vie.o Cailloux.o Malus.o Trou.o Piece.o Jeu.o

all : $(addprefix $(BIN_PATH), $(EXEC_NAME))

clean :
	rm $(addprefix $(BIN_PATH), $(EXEC_NAME)) $(addprefix $(OBJ_PATH), $(OBJ_FILES))

$(addprefix $(BIN_PATH), $(EXEC_NAME)) : $(addprefix $(OBJ_PATH), $(OBJ_FILES))
	$(CC) $(CFLAGS) -o $(addprefix $(BIN_PATH), $(EXEC_NAME)) $(addprefix $(OBJ_PATH), $(OBJ_FILES)) $(LIBS)

$(addprefix $(OBJ_PATH), %.o): $(addprefix $(SRC_PATH), %.cc)
	$(CC) $(CFLAGS) -o $@ -c $<

$(addprefix $(OBJ_PATH), %.o): $(addprefix $(SRC_PATH), %.cc) $(addprefix $(SRC_PATH), %.hh)
	$(CC) $(CFLAGS) -o $@ -c $<
