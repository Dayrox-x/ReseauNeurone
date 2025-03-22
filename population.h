#ifndef POPULATION_H
#define POPULATION_H

/**
 * \file population.h
 * \brief Fonctions de gestion des populations (création, destruction, modification)
 * \author Simon Cossais
 * \author Paul Sarazin
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <SDL2/SDL.h>

/**
 * \typedef SDL_Color* Color
 * \brief Pointeur sur une structure de type SDL_Color
 */
typedef SDL_Color* Color;

/**
 * \struct pxl
 * \brief Structure d'un Pixel
 * 
 * \var pxl::x
 * Coordonnée en abscisse du pixel
 * \var pxl::y
 * Coordonnée en ordonnée du pixel
 * \var pxl::color
 * Couleur du pixel
 */
typedef struct {
    double x;
    double y;
    Color color;
} pxl;

/**
 * \typedef pxl* Pixel
 * \brief Pointeur sur une structure pxl
 */
typedef pxl* Pixel;

/**
 * \struct img
 * \brief Structure d'une Image
 * \var img::tab
 * Tableau à 2 dimensions de Pixel
 * \var img::width
 * Largeur du tableau
 * \var img::height
 * Hauteur du tableau
 */
typedef struct {
    Pixel** tab;
    int width, height;
} img;

/**
 * \typedef img* Image
 * \brief Pointeur sur une structure pxl
 */
typedef img* Image;

/**
 * \struct data
 * \brief Structure d'un jeu de donnée Dataset
 * \var data::tab
 * Tableau de pixel
 * \var data::size
 * Taille du jeu de donnée
 */
typedef struct {
    Pixel* tab;
    int size;
} data;

/**
 * \typedef data* Dataset
 * \brief Pointeur sur une structure data
 */
typedef data* Dataset;

// getters setters de Color
/**
 * \brief Définit la valeur de r (rouge) de la couleur c
 * \param c
 * Couleur dont on modifie la valeur de r
 * \param r
 * Nouvelle valeur de r, fait modulo 256
 */
void setR(Color c, int r);

/**
 * \brief Renvoie la valeur de r d'une couleur
 * \param c
 * Couleur dont on renvoie la valeur de r
 */
int getR(Color c);

/**
 * \brief Définit la valeur de g (vert) de la couleur c
 * \param c
 * Couleur dont on modifie la valeur de g
 * \param r
 * Nouvelle valeur de g, fait modulo 256
 */
void setG(Color c, int g);

/**
 * \brief Renvoie la valeur de g
 * \param c
 * Couleur dont on renvoie la valeur de g
 */
int getG(Color c);

/**
 * \brief Définit la valeur de b (bleu) de la couleur c
 * \param c
 * Couleur dont on modifie la valeur de b
 * \param r
 * Nouvelle valeur de b, fait modulo 256
 */
void setB(Color c, int b);

/**
 * \brief Renvoie la valeur de b
 * \param c
 * Couleur dont on renvoie la valeur de b
 */
int getB(Color c);

/**
 * \brief Définit la valeur de a (alpha = opacité) de la couleur c
 * \param c
 * Couleur dont on modifie la valeur de a
 * \param r
 * Nouvelle valeur de a, fait modulo 256
 */
void setA(Color c, int a);

/**
 * \brief Renvoie la valeur de a
 * \param c
 * Couleur dont on renvoie la valeur de a
 */
int getA(Color c);

/**
 * \brief Alloue et crée une couleur depuis des valeur RGBA, penser à utiliser destroyColor
 * \param r
 * Intensité de la couleur rouge
 * \param g
 * Intensité de la couleur verte
 * \param b
 * Intensité de la couleur bleue
 * \param a
 * Opacité de la couleur
 * \return Couleur créée
 */
Color createColor(int r, int g, int b, int a);

/**
 * \brief Détruit une couleur
 * \param c
 * Color a détruire
 */
void destroyColor(Color c);

// getters setters de Pixel

/**
 * \brief Définit la couleur d'un pixel
 * \param p
 * Pixel dont on définit la couleur
 * \param c
 * Nouvelle couleur du pixel
 */
void setColor(Pixel p, Color c);

/**
 * \brief Renvoie la couleur d'un pixel
 * \param p
 * Pixel dont on récupère la couleur
 * \return Couleur du pixel p
 */
Color getColor(Pixel p);

/**
 * \brief Définit la position x d'un pixel
 * \param p
 * Pixel dont on définit la position
 * \param x
 * Nouvelle position en abscisse du pixel
 */
void setX(Pixel p, double x);

/**
 * \brief Renvoie la position en abscisse d'un pixel
 * \param p
 * Pixel dont on récupère la position
 * \return Coordonnée x du Pixel
 */
double getX(Pixel p);

/**
 * \brief Définit la position y d'un pixel
 * \param p
 * Pixel dont on définit la position
 * \param y
 * Nouvelle position en ordonnée du pixel
 */
void setY(Pixel p, double y);

/**
 * \brief Renvoie la position en ordonnée d'un pixel
 * \param p
 * Pixel dont on récupère la position
 * \return Coordonnée x du Pixel
 */
double getY(Pixel p);

/**
 * \brief Alloue et crée un pixel depuis des coordonnées et une couleur, penser à utiliser destroyPixel
 * \param x
 * Position en abscisse du nouveau pixel
 * \param y
 * Position en ordonnée du nouveau pixel
 * \param c
 * Couleur du nouveau pixel
 * \return Pixel créé
 */
Pixel createPixel(double x, double y, Color c);

/**
 * \brief Détruit un pixel
 * \param p
 * Pixel dont on libère l'espace
 */
void destroyPixel(Pixel p);

// getters setters de Image

/**
 * \brief Retourne le pixel de position (x, y) dans une image
 * \param image
 * Image dont on récupère le pixel
 * \param x
 * Position en abscisse du pixel voulu
 * \param y
 * Position en ordonnée du pixel voulu
 * \return Pixel de position (x, y) dans l'image
 */
Pixel getPixel(Image image, int x, int y);

/**
 * \brief Définit le pixel de position (x, y) dans une image
 * \param image Image dont on définit le pixel
 * \param x
 * Position en abscisse du pixel défini
 * \param y
 * Position en ordonnée du pixel défini
 * \param p
 * Pixel que l'on place dans l'image
 */
void setPixel(Image image, int x, int y, Pixel p);

/**
 * \brief Retourne la largeur d'une image
 * \param image
 * Image dont on récupère la largeur
 * \return Largeur de l'image
 */
int getWidth(Image image);

/**
 * \brief Retourne la hauteur d'une image
 * \param image
 * Image dont on récupère la hauteur
 * \return Hauteur de l'image
 */
int getHeight(Image image);

/**
 * \brief Retourne la couleur du pixel de coordonnées (x, y) dans une image
 * \param image
 * Image dont on veut récupérer le couleur d'un des pixels
 * \param x
 * Position en abscisse du pixel dans l'image
 * \param y
 * Position en ordonnée du pixel dans l'image
 * \return Couleur du pixel sélectionné
 */
Color getPixelColor(Image image, int x, int y);

/**
 * \brief Définit la couleur du pixel de coordonnées (x, y) dans une image
 * \param image
 * Image dont on définit la couleur d'un des pixels
 * \param x
 * Position en abscisse du pixel dans l'image
 * \param y
 * Position en ordonnée du pixel dans l'image
 * \param c
 * Nouvelle couleur du pixel
 */
void setPixelColor(Image image, int x, int y, Color c);

/**
 * \brief Alloue et crée un tableau à deux dimensions de pixels, ne pas oublier d'utiliser destroyPixelTab
 * \param width
 * Largeur du tableau
 * \param height
 * Hauteur du tableau
 * \param c
 * Couleur des pixels du tableau
 * \return Tableau de taille width*height de pixels de couleur c
 */
Pixel** createPixelTab(int width, int height, Color c);

/**
 * \brief Alloue et crée une image, ne pas oublier d'utiliser destroyImage
 * \param width
 * Largeur de l'image
 * \param height
 * Hauteur de l'image
 * \param c
 * Couleur des pixels de l'image
 * \return Image de taille width*height de couleur c
 */
Image createImage(int width, int height, Color c);

/**
 * \brief Détruit un tableau de pixels
 * \param tab
 * Tableau de Pixel à détruire
 * \param width
 * Largeur du tableau
 * \param height
 * Hauteur du tableau
 */
void destroyPixelTab(Pixel ** tab, int width, int height);

/**
 * \brief Détruit une Image
 * \param image
 * Image à détruire
 */
void destroyImage(Image image);


// getters setters de Dataset

/**
 * \brief Renvoie la taille du jeu de donnée passé en paramètre
 * \param dataset
 * Jeu de donnée dont on récupère la taille
 * \return Taille du jeu de donnée
 */
int getDatasetSize(Dataset dataset);

/**
 * \brief Alloue l'espace pour un jeu de donnée vide, ne pas oublier d'utiliser destroyDataset
 * \return Dataset vide
 */
Dataset createDataset();

/**
 * \brief Ajoute un pixel a un jeu de donnée
 * \param d
 * Jeu de donnée
 * \param p
 * Pixel a ajouter
 */
void addDatasetPixel(Dataset d, Pixel p);

/**
 * \brief Détruit un Dataset
 * \param dataset
 * Dataset a détruire
 */
void destroyDataset(Dataset dataset);

/**
 * \brief Renvoie le ième Pixel du Dataset
 * \param dataset
 * Dataset dont on récupère un pixel
 * \param i
 * Position du pixel a récupérer
 * \return Pixel en ième position dans le Dataset
 */
Pixel getDatasetPixel(Dataset dataset, int i);


/**
 * \brief Crée une population de pixels de couleur c selon les fonctions géométriques sin et cos
 * \param d
 * Dataset dans laquelle est crée la population
 * \param c
 * Couleur de la population
 * \param val
 * valeur du multiplicateur appliqué à sin et cos
 */
void createPopulation(Dataset d, Color c, double val, int size);

/**
 * \brief Crée une spirale rouge et noire
 * \param d
 * Dataset dans lequel est créée la spirale
 */
void createSpiral(Dataset d);

#endif
