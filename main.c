#include <SDL2/SDL.h>
 
int main( int argc, char* args[] ) { 
	//Demarrer SDL 
	SDL_Init( SDL_INIT_EVERYTHING ); 

	SDL_Window* window = SDL_CreateWindow( "SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0 );
	SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	
 
	//Quitter SDL 
	SDL_Quit(); 
 
	return 0; 
}
