/**
 * \file main.c
 * \brief Programme de reseau de neurones.
 * \author user
 * \version 0.1
 * \date 11 septembre 2007
 *
 * Programme de reseau de neurones.
 * Main démarre et quitte SDL
 *
 */


#include "SDL2/SDL.h"
 
/**
 * \fn int main(int argc, char* args[])
 * \brief Fonction main
 *
 * \param argc argument
 * \param args[] tableau d'argument
 * \return 0
 */
int main(int argc, char* args[] ) { 
	//Demarrer SDL 
	SDL_Init( SDL_INIT_EVERYTHING ); 
 
	//Quitter SDL 
	SDL_Quit(); 
 
	return 0; 
}
