CC = g++
CFLAGS = -Isrc/include -Lsrc/lib -mwindows
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
#LIBS = -lmingw32 -lSDL2main -lSDL2 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc -lSDL2_image -lSDL2_ttf
EXECUTABLE = Jogo.exe

# Objetos
OBJECTS = main.o Game.o TextHandler.o Jogador.o Projetil.o Meteoro.o MenuButton.o

# Regras
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	del $(EXECUTABLE) $(OBJECTS)