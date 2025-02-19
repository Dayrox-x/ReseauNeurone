#include <SDL2/SDL.h>
#include "population.h"
#include "sdl.h"

void afficherPoints(SDL_Window *window, Image image) {
    if (window == NULL) {
        printf("Erreur : fenêtre SDL non valide.\n");
        return;
    }

    if (image.tab == NULL) {
        printf("Erreur : image.tab est NULL\n");
        return;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur : impossible de créer le renderer SDL.\n");
        return;
    }
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderClear(renderer);
    
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            Pixel p = getPixel(image, x, y);
            Color c = getColor(p);
            if (getR(c) != 0 || getG(c) != 0 || getB(c) != 0) { // Ignorer les pixels noirs par défaut
                SDL_SetRenderDrawColor(renderer, getR(c), getG(c), getB(c), 255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
    
    SDL_RenderPresent(renderer);
    SDL_DestroyRenderer(renderer);
}
