#ifndef SDL_H
#define SDL_H

#include "population.h"
#include <SDL2/SDL.h>
#include <assert.h>

/**
 * \fn void renderImage(Image image, SDL_Renderer* renderer, SDL_Window* window, int pxl_size)
 * \brief Affiche l'image passée en paramètre dans la fenetre SDL
 * \param image
 * Image a afficher
 * \param renderer
 * Pointeur sur le renderer utilisé pour afficher l'image
 * \param window
 * Pointeur sur la fenetre SDL dans laquelle s'affiche l'image
 * \param pxl_size
 * Taille du pixel utilisé
 */
void renderImage(Image image, SDL_Renderer* renderer, SDL_Window* window, int pxl_size);

/**
 * \fn void renderDataset(Dataset d, SDL_Renderer* renderer, SDL_Window* window, int pxl_size)
 * \brief Affiche le jeu de donnée passé en paramètre dans la fenetre SDL
 * \param d
 * Dataset a afficher
 * \param renderer
 * Pointeur sur le renderer utilisé pour afficher l'image
 * \param window
 * Pointeur sur la fenetre SDL dans laquelle s'affiche l'image
 * \param pxl_size
 * Taille du pixel utilisé
 */
void renderDataset(Dataset d, SDL_Renderer* renderer, SDL_Window* window, int pxl_size);

#endif
