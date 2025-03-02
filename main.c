#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "neuron.h"
#include "population.h"
#include "sdl.h"

// pour compiler : gcc *.c -g -o main -lm -lSDL2
// -lm pour la librairie mathematique, -lSDL2 pour la librairie SDL2
// pour executer : ./main
// SFML et Doxygen

#define PIXEL_SIZE 10
#define WIDTH 640/PIXEL_SIZE
#define HEIGHT 640/PIXEL_SIZE
 
int main( int argc, char* args[] ) {
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

	Color white = createColor(255, 255, 255, 255);
	Color red = createColor(255, 0, 0, 255);
	Color blue = createColor(0, 0, 255, 255);

	SDL_Rect pixel = {0, 0, PIXEL_SIZE, PIXEL_SIZE};

	Image image = createImage(WIDTH, HEIGHT, white);

	createPopulation(image, PIXEL_SIZE, red, false);
	createPopulation(image, PIXEL_SIZE, blue, true);

	for (int i = 0; i < getWidth(image); i++) {
		for (int j = 0; j < getHeight(image); j++) {
			// evite le msg d'erreur "la fenetre ne repond pas"
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					SDL_DestroyRenderer( renderer );
					SDL_DestroyWindow( window );
					SDL_Quit();
					destroyImage(image);
					return 0;
				}
			}

			ret = SDL_SetRenderDrawColor( renderer, getR(getPixelColor(image, i, j)), getG(getPixelColor(image, i, j)), getB(getPixelColor(image, i, j)), getA(getPixelColor(image, i, j)) );
			assert(ret == 0 && "SDL_SetRenderDrawColor failed");

			pixel.x = i * PIXEL_SIZE;
			pixel.y = j * PIXEL_SIZE;
			ret = SDL_RenderFillRect( renderer, &pixel);
			assert(ret == 0 && "SDL_RenderFillRect failed");

			SDL_RenderPresent( renderer );
		}
	}

	destroyImage(image);

	destroyColor(white);
	destroyColor(red);
	destroyColor(blue);


	SDL_Delay(5000);

	SDL_RenderPresent( renderer );
 
	//Quitter SDL 
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit(); 
 
	return 0; 
}