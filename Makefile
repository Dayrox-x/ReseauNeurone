CC = gcc    #définit le compilateur
CFLAGS = -Wall -g   # Options de compilation (affichage des warnings et debug)
LIBS = -lSDL2 -lm # # Bibliothèques
SRC = main.c neuron.c population.c sdl.c backpropagation.c saveRead.c
OBJ = $(SRC:.c=.o)
EXEC = reseau

all: $(EXEC) # Règle par défaut pour construire l'exécutable

$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
