CC = g++
CFLAGS = -Wall
EXEC_NAME = jeu
INCLUDES = 
LIBS = -lSDL2 -lSDL2_image
OBJ_FILES = main.o

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.cc %.hh
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

