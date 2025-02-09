#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "neuron.h"
#include "population.h"
#include "sdl.h"

// pour compiler : gcc *.c -o main -lm -lSDL2
// -lm pour la librairie mathematique, -lSDL2 pour la librairie SDL2
// pour executer : ./main
 
int main( int argc, char* args[] ) { 
	//Demarrer SDL 
	SDL_Init( SDL_INIT_EVERYTHING ); 

	SDL_Window* window = SDL_CreateWindow( "SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0 );
	SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
 
	//Quitter SDL 
	SDL_Quit(); 
 
	return 0; 
}
