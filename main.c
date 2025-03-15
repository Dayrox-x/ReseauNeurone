#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "neuron.h"
#include "population.h"
#include "sdl.h"
#include "backpropagation.h"

// pour compiler : gcc *.c -g -o main -lm -lSDL2
// -lm pour la librairie mathematique, -lSDL2 pour la librairie SDL2
// pour executer : ./main

#define PIXEL_SIZE 20
#define WIDTH 640/PIXEL_SIZE
#define HEIGHT 640/PIXEL_SIZE
 
int main( int argc, char* args[] ) {
	
	srand(time(NULL));

	Color white = createColor(255, 255, 255, 255);
	Color red = createColor(255, 0, 0, 255);
	Color blue = createColor(0, 0, 255, 255);

	Image image = createImage(WIDTH, HEIGHT, white);

	Dataset d = createDataset();

	createPopulation(image, d, red, 1);
	createPopulation(image, d, blue, -1);

	Couche* reseau = init_reseau(20, 5, 5, 2, 2);
	
	learn(reseau, d, 0.01, 0.001);
	print_reseau(reseau);

	//Demarrer SDL 
	int ret = SDL_Init( SDL_INIT_VIDEO );
	assert(ret == 0 && "SDL_Init failed");

	SDL_Window* window = SDL_CreateWindow( "SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE, SDL_WINDOW_SHOWN );
	assert(window != NULL && "SDL_CreateWindow failed");

	SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_SOFTWARE );
	assert(renderer != NULL && "SDL_CreateRenderer failed");

	ret = SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	assert(ret == 0 && "SDL_SetRenderDrawColor failed");

	ret = SDL_RenderClear( renderer );
	assert(ret == 0 && "SDL_RenderClear failed");

	SDL_Rect pixel = {0, 0, PIXEL_SIZE, PIXEL_SIZE};

	renderImage(image, renderer, window, pixel, PIXEL_SIZE);

	bool end = false;
	SDL_Event e;
	while(!end) {
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
			{
				end = true;
			}
		}
		generalize(reseau, image);
		renderImage(image, renderer, window, pixel, PIXEL_SIZE);
	}

	//Quitter SDL 
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
	
	destroyImage(image);

	destroyColor(white);
	destroyColor(red);
	destroyColor(blue);

	destroyDataset(d);
	free_reseau(reseau);
 

	return 0; 
}