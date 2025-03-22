#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "neuron.h"
#include "population.h"
#include "sdl.h"
#include "backpropagation.h"
#include "log.h"

// pour compiler : gcc *.c -g -o main -lm -lSDL2
// -lm pour la librairie mathematique, -lSDL2 pour la librairie SDL2
// pour executer : ./main

#define PIXEL_SIZE 10
#define WIDTH 640/PIXEL_SIZE
#define HEIGHT 640/PIXEL_SIZE
#define EPSILON 0.001
#define THRESHOLD 0.001
 
int main( int argc, char* args[] ) {
	log_info("Démarrage du programme");
	srand(time(NULL));

	log_debug("Initialisation des couleurs");
	Color black = createColor(0, 0, 0, 255);
	Color red = createColor(255, 0, 0, 255);
	Color blue = createColor(0, 0, 255, 255);
	log_info("Couleurs initialisées");

	log_debug("Création de l'image");
	Image image = createImage(WIDTH, HEIGHT, black);
	log_info("Image créée avec taille %dx%d", WIDTH, HEIGHT);

	Dataset d = createDataset();

	createSpiral(d);

	log_debug("Initialisation du réseau de neurones");
	Couche* reseau = init_reseau(7, 128, 64, 2, 2);
	if (!reseau) {
        log_fatal("Échec de l'initialisation du réseau");
        destroyImage(image);
        destroyColor(red);
        destroyColor(blue);
        return EXIT_FAILURE;
    }
	log_info("Réseau de neurones initialisé");
	
	log_warn("Début de l'apprentissage");
	learn(reseau, d, EPSILON, THRESHOLD);
	log_info("Fin de l'apprentissage");

	//Demarrer SDL
	log_debug("Initialisation de SDL");
	int ret = SDL_Init( SDL_INIT_VIDEO );
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        log_fatal("Échec de SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
	log_info("SDL initialisé avec succès");

	SDL_Window* window = SDL_CreateWindow( "SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE, SDL_WINDOW_SHOWN );
	if (!window) {
        log_fatal("Échec de SDL_CreateWindow : %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
	log_info("Fenêtre SDL créée avec succès");

	SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_SOFTWARE );
	if (!renderer) {
        log_fatal("Échec de SDL_CreateRenderer : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
	log_info("Renderer SDL créé avec succès");

	ret = SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	if (!renderer) {
		log_fatal("Échec de SDL_SetRenderDrawColor : %s", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	log_info("Couleur de rendu définie avec succès");

	ret = SDL_RenderClear( renderer );
	if (!renderer) {
		log_fatal("Échec de SDL_RenderClear : %s", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	log_info("Renderer nettoyé avec succès");

	renderImage(image, renderer, window, PIXEL_SIZE);

	renderDataset(d, renderer, window, PIXEL_SIZE);

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
		renderImage(image, renderer, window, PIXEL_SIZE);
		learn(reseau, d, EPSILON, THRESHOLD);
	}

	//Quitter SDL 
	log_debug("Libération des ressources");
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
	log_info("Ressources libérées, fin du programme");
	
	destroyImage(image);

	destroyColor(black);
	destroyColor(red);
	destroyColor(blue);

	destroyDataset(d);
	free_reseau(reseau);
 

	return 0; 
}