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
Pixel getPixel(Image image, int x, int y);
void setPixel(Image image, int x, int y, Pixel p);

int getWidth(Image image);
int getHeight(Image image);

Color getPixelColor(Image image, int x, int y);
void setPixelColor(Image image, int x, int y, Color c);

Pixel** createPixelTab(int width, int height, Color c);

Image createImage(int width, int height, Color c);

void destroyPixelTab(Pixel ** tab, int width, int height);
void destroyImage(Image image);

void createPopulation(Image image, int populationSize, Color c, bool val);

#endif