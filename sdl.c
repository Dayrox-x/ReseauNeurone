#include "sdl.h"

void renderImage(Image image, SDL_Renderer* renderer, SDL_Window* window, SDL_Rect pixel, int pxl_size) {
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
					return;
				}
			}

			int ret = SDL_SetRenderDrawColor( renderer, getR(getPixelColor(image, i, j)), getG(getPixelColor(image, i, j)), getB(getPixelColor(image, i, j)), getA(getPixelColor(image, i, j)) );
			assert(ret == 0 && "SDL_SetRenderDrawColor failed");

			pixel.x = i * pxl_size;
			pixel.y = j * pxl_size;
			ret = SDL_RenderFillRect( renderer, &pixel);
			assert(ret == 0 && "SDL_RenderFillRect failed");

			SDL_RenderPresent( renderer );
		}
	}
}
