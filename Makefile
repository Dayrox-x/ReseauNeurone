CC = gcc    #définit le compilateur
CFLAGS = -Wall -g   # Options de compilation (affichage des warnings et debug)
LIBS = -lSDL2 -lm # # Bibliothèques
SRC = main.c neuron.c population.c sdl.c backpropagation.c log.c saveRead.c
OBJ = $(SRC:.c=.o)
EXEC = reseau

# Nom de l'exécutable principal
PROJECT  = main

# Nom de l'exécutable des benchmarks
BENCHMARK = benchmark

# Fichiers sources pour l'exécutable principal
SRCS = main.c sdl.c population.c backpropagation.c neuron.c log.c saveRead.c

# Fichiers sources pour les benchmarks
BENCHMARK_SRCS = benchmark.c sdl.c population.c backpropagation.c neuron.c 

# Fichiers objets pour l'exécutable principal
OBJS = $(SRCS:.c=.o)

# Fichiers objets pour les benchmarks
BENCHMARK_OBJS = $(BENCHMARK_SRCS:.c=.o)

# Drapeaux de compilation
CFLAGS = -g -lm -lSDL2

# Règle pour compiler le projet principal
$(PROJECT): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o $(PROJECT)

# Règle pour compiler les benchmarks
$(BENCHMARK): $(BENCHMARK_SRCS)
	$(CC) $(BENCHMARK_SRCS) $(CFLAGS) -o $(BENCHMARK)

# Règle pour exécuter le projet principal
run: $(PROJECT)
	./$(PROJECT)

# Règle pour exécuter les benchmarks
run_benchmarks: $(BENCHMARK)
	./$(BENCHMARK)

# Nettoyer les fichiers compilés
clean:
	rm -f $(PROJECT) $(BENCHMARK) *.cls
