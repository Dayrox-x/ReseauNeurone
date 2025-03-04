#ifndef POPULATION_H
#define POPULATION_H

/**
 * \file population.h
 * \brief Fonctions de gestion des populations (création, destruction, modifications)
 * \author Simon Cossais
 * \author Paul Sarazin
 * \date 28/02/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

/**
 * \typedef SDL_Color* Color
 * \brief Pointeur sur une structure de type SDL_Color
 */
typedef SDL_Color* Color;

/**
 * \struct pxl
 * 
 * \var int x
 * Coordonnée en abscisse du pxl
 * \var int y
 * Coordonnée en ordonnée du pxl
 * \var Color color
 * Couleur du pxl
 */
typedef struct {
    int x;
    int y;
    Color color; // RGB
} pxl;

/**
 * \typedef pxl* Pixel
 * \brief Pointeur sur une structure pxl
 */
typedef pxl* Pixel;

/**
 * \struct img
 * 
 * \var Pixel** tab
 * Tableau à 2 dimensions de Pixel
 * \var int width
 * Largeur du tableau
 * \var int height
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

// getters setters de Color
/**
 * \fn void setR(Color c, int r)
 * \brief Définie la valeur de r (rouge) de la couleur c
 * \param c
 * Couleur dont on modifie la valeur de r
 * \param r
 * Nouvelle valeur de c->r, fait modulo 256
 */
void setR(Color c, int r);

/**
 * \fn int getR(Color c)
 * \brief Renvoie la valeur de c->r
 * \param c
 * Couleur dont on renvoie la valeur de r
 */
int getR(Color c);

/**
 * \fn void setG(Color c, int g)
 * \brief Définie la valeur de g (vert) de la couleur c
 * \param c
 * Couleur dont on modifie la valeur de g
 * \param r
 * Nouvelle valeur de c->g, fait modulo 256
 */
void setG(Color c, int g);

/**
 * \fn int getG(Color c)
 * \brief Renvoie la valeur de c->g
 * \param c
 * Couleur dont on renvoie la valeur de g
 */
int getG(Color c);

/**
 * \fn void setB(Color c, int b)
 * \brief Définie la valeur de b (bleu) de la couleur c
 * \param c
 * Couleur dont on modifie la valeur de b
 * \param r
 * Nouvelle valeur de c->b, fait modulo 256
 */
void setB(Color c, int b);

/**
 * \fn int getB(Color c)
 * \brief Renvoie la valeur de c->b
 * \param c
 * Couleur dont on renvoie la valeur de b
 */
int getB(Color c);

/**
 * \fn void setA(Color c, int a)
 * \brief Définie la valeur de a (alpha = opacité) de la couleur c
 * \param c
 * Couleur dont on modifie la valeur de a
 * \param r
 * Nouvelle valeur de c->a, fait modulo 256
 */
void setA(Color c, int a);

/**
 * \fn int getA(Color c)
 * \brief Renvoie la valeur de c->a
 * \param c
 * Couleur dont on renvoie la valeur de a
 */
int getA(Color c);

/**
 * \fn Color createColor(int r, int g, int b, int a)
 * \brief Alloue et crée une couleur depuis des valeur RGBa, penser à utiliser destroyColor
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
 * \fn void destroyColor(Color c)
 * \brief Détruit une couleur
 * \param c
 * Color a détruire
 */
void destroyColor(Color c);

// getters setters de Pixel

/**
 * \fn void setColor(Pixel p, Color c)
 * \brief Définie la couleur d'un pixel
 * \param p
 * Pixel dont on définie la couleur
 * \param c
 * Nouvelle couleur du pixel
 */
void setColor(Pixel p, Color c);

/**
 * \fn Color getColor(Pixel p)
 * \brief Renvoie la couleur d'un pixel
 * \param p
 * Pixel dont on récupère la couleur
 * \return Couleur du pixel p
 */
Color getColor(Pixel p);

/**
 * \fn void setX(Pixel p, int x)
 * \brief Définie la position x d'un pixel
 * \param p
 * Pixel dont on définie la position
 * \param x
 * Nouvelle position en abscisse du pixel
 */
void setX(Pixel p, int x);

/**
 * \fn int getX(Pixel p)
 * \brief Renvoie la position en abscisse d'un pixel
 * \param p
 * Pixel dont on récupère la position
 */
int getX(Pixel p);

/**
 * \fn void setY(Pixel p, int y)
 * \brief Définie la position y d'un pixel
 * \param p
 * Pixel dont on définie la position
 * \param y
 * Nouvelle position en ordonnée du pixel
 */
void setY(Pixel p, int y);

/**
 * \fn int getY(Pixel p)
 * \brief Renvoie la position en ordonnée d'un pixel
 * \param p
 * Pixel dont on récupère la position
 */
int getY(Pixel p);

/**
 * \fn Pixel createPixel(int x, int y, Color c)
 * \brief Alloue et crée un pixel depuis des coordonnées et une couleur, penser à utiliser destroyPixel
 * \param x
 * Position en abscisse du nouveau pixel
 * \param y
 * Position en ordonnée du nouveau pixel
 * \param c
 * Couleur du nouveau pixel
 * \return Pixel créé
 */
Pixel createPixel(int x, int y, Color c);

/**
 * \fn void destroyPixel(Pixel p)
 * \brief Détruit un pixel, ne détruit pas la couleur
 * \param p
 * Pixel dont on libère l'espace
 */
void destroyPixel(Pixel p);

// getters setters de Image

/**
 * \fn Pixel getPixel(Image image, int x, int y)
 * \brief Retourne le pixel de position (x, y) dans une image
 * \param image
 * Image dont on récupère le pixel
 * \param x
 * Position en abscisse du pixel voulu
 * \param y
 * Position en ordonnée du pixel voulu
 * \return Pixel de position x, y
 */
Pixel getPixel(Image image, int x, int y);

/**
 * \fn void setPixel(Image image, int x, int y, Pixel p)
 * \brief Définie le pixel de position (x, y) dans une image
 * \param image Image dont on définie le pixel
 * \param x
 * Position en abscisse du pixel défini
 * \param y
 * Position en ordonnée du pixel défini
 * \param p
 * Pixel que l'on place dans l'image
 */
void setPixel(Image image, int x, int y, Pixel p);

/**
 * \fn int getWidth(Image image)
 * \brief Retourne la largeur d'une image
 * \param image
 * Image dont on récupère la largeur
 * \return Largeur de l'image
 */
int getWidth(Image image);

/**
 * \fn int getHeight(Image image)
 * \brief Retourne la hauteur d'une image
 * \param image
 * Image dont on récupère la hauteur
 * \return Hauteur de l'image
 */
int getHeight(Image image);

/**
 * \fn Color getPixelColor(Image image, int x, int y)
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
 * \fn void setPixelColor(Image image, int x, int y, Color c)
 * \brief Définie la couleur du pixel de coordonnées (x, y) dans une image
 * \param image
 * Image dont on définie la couleur d'un des pixels
 * \param x
 * Position en abscisse du pixel dans l'image
 * \param y
 * Position en ordonnée du pixel dans l'image
 * \param c
 * Nouvelle couleur du pixel
 */
void setPixelColor(Image image, int x, int y, Color c);

/**
 * \fn Pixel** createPixelTab(int width, int height, Color c)
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
 * \fn Image createImage(int width, int height, Color c)
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
 * \fn void destroyPixelTab(Pixel ** tab, int width, int height)
 * \brief Détruit un tableau de pixels, ne détruit pas les couleurs associées
 * \param tab
 * Tableau de Pixel à détruire
 * \param width
 * Largeur du tableau
 * \param height
 * Hauteur du tableau
 */
void destroyPixelTab(Pixel ** tab, int width, int height);

/**
 * \fn void destroyImage(Image image)
 * \brief Détruit une Image, ne détruit pas les couleur associées aux pixels
 * \param image
 * Image à détruire
 */
void destroyImage(Image image);

/**
 * \fn void createPopulation(Image image, int populationSize, Color c, bool val)
 * \brief Crée une population de pixels de couleur c selon les fonctions géométriques sin et cos
 * \param image
 * Image dans laquelle est crée la population
 * \param c
 * Couleur de la population
 * \param val
 * valeur du multiplicateur appliqué à sin et cos
 */
void createPopulation(Image image, Color c, int val);

#endif