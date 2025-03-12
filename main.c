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

#define PIXEL_SIZE 10
#define WIDTH 640/PIXEL_SIZE
#define HEIGHT 640/PIXEL_SIZE

// pour compiler : gcc *.c -g -o main -lm -lSDL2
// -lm pour la librairie mathematique, -lSDL2 pour la librairie SDL2
// pour executer : ./main
// SFML et Doxygen

int main(int argc, char* args[]) {
    log_info("Démarrage du programme");

    log_debug("Initialisation de SDL");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        log_fatal("Échec de SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    log_info("SDL initialisé avec succès");

    SDL_Window* window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE, SDL_WINDOW_SHOWN);
    if (!window) {
        log_fatal("Échec de SDL_CreateWindow : %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    log_info("Fenêtre SDL créée avec succès");

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) {
        log_fatal("Échec de SDL_CreateRenderer : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    log_info("Renderer SDL créé avec succès");

    // Définition des couleurs
    log_debug("Initialisation des couleurs");
    Color red = createColor(255, 0, 0, 255);
    Color blue = createColor(0, 0, 255, 255);
    log_info("Couleurs initialisées");

    // Création de l'image
    log_debug("Création de l'image");
    Image image = createImage(WIDTH, HEIGHT, blue);
    log_info("Image créée avec taille %dx%d", WIDTH, HEIGHT);

    // Initialisation du réseau de neurones
    log_debug("Initialisation du réseau de neurones");
    Couche* reseau = init_reseau(10, 5, 2, 2, 2);
    if (!reseau) {
        log_fatal("Échec de l'initialisation du réseau");
        destroyImage(image);
        destroyColor(red);
        destroyColor(blue);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    log_info("Réseau de neurones initialisé");

    // Affichage du réseau avant apprentissage
    log_debug("Affichage du réseau avant apprentissage");
    print_reseau(reseau);

    // Phase d'apprentissage
    log_warn("Début de l'apprentissage");
    learn(reseau, image, 0.001, 0.01);
    log_info("Fin de l'apprentissage");

    // Affichage du réseau après apprentissage
    log_debug("Affichage du réseau après apprentissage");
    print_reseau(reseau);

    // Nettoyage des ressources
    log_debug("Libération des ressources");
    destroyImage(image);
    destroyColor(red);
    destroyColor(blue);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    log_info("Ressources libérées, fin du programme");

    return EXIT_SUCCESS;
}
