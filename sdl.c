#include "sdl.h"

#define MAX_TEXT_LENGTH 128  // Taille maximale du nom de fichier

void renderImage(Image image, SDL_Renderer* renderer, SDL_Window* window, SDL_Rect pixel, int pxl_size) {
    for (int i = 0; i < getWidth(image); i++) {
		for (int j = 0; j < getHeight(image); j++) {
			int ret = SDL_SetRenderDrawColor( renderer, getR(getPixelColor(image, i, j)), getG(getPixelColor(image, i, j)), getB(getPixelColor(image, i, j)), getA(getPixelColor(image, i, j)) );
			assert(ret == 0 && "SDL_SetRenderDrawColor failed");

			pixel.x = i * pxl_size;
			pixel.y = j * pxl_size;
			ret = SDL_RenderFillRect( renderer, &pixel);
			assert(ret == 0 && "SDL_RenderFillRect failed");
		}
	}
	SDL_RenderPresent( renderer );
}

void renderDataset(Dataset d, SDL_Renderer* renderer, SDL_Window* window, SDL_Rect pixel, int pxl_size){
	for (int i = 0; i < getDatasetSize(d); i++){
		SDL_SetRenderDrawColor(renderer, getR(getColor(getDatasetPixel(d, i))), getG(getColor(getDatasetPixel(d, i))), getB(getColor(getDatasetPixel(d, i))), getA(getColor(getDatasetPixel(d, i))));
		
		int width = 0;
		int height = 0;

		SDL_GetWindowSize(window, &width, &height);
		
		pixel.x = (int)(getX(getDatasetPixel(d, i))) + width / 2;
		pixel.y = (int)(getY(getDatasetPixel(d, i))) + height / 2;

		SDL_RenderFillRect(renderer, &pixel);
	}
	SDL_RenderPresent(renderer);
}


void inputNameFicSave(char* output) {
    SDL_Event event;
    int running = 1;
    char inputText[MAX_TEXT_LENGTH + 4] = "";  // Stocke le texte saisi
    SDL_StartTextInput();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                break;
            } else if (event.type == SDL_TEXTINPUT) {
                // Ajouter du texte si la limite n'est pas atteinte
                if (strlen(inputText) + strlen(event.text.text) < MAX_TEXT_LENGTH) {
                    strcat(inputText, event.text.text);
                }
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0) {
                    inputText[strlen(inputText) - 1] = '\0';  // Supprime le dernier caractère
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    running = 0;  // Fin de la saisie
                }
            }
        }

        // Affichage simplifié du texte (ex: afficher dans la console)
        printf("\r%s    ", inputText);  // Mise à jour du texte affiché
        fflush(stdout);
    }

    SDL_StopTextInput();
	strcat(inputText, ".cls");
	strcpy(output, inputText);
    printf("\nFichier ouvert : %s\n", output);
}
