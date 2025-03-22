#include "sdl.h"

void renderImage(Image image, SDL_Renderer* renderer, SDL_Window* window, int pxl_size) {
	SDL_Rect pixel = {0, 0, pxl_size, pxl_size};
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

void renderDataset(Dataset d, SDL_Renderer* renderer, SDL_Window* window, int pxl_size){
	SDL_Rect pixel = {0, 0, pxl_size, pxl_size};
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
