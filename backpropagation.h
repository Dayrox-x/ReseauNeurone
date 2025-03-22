#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "neuron.h"
#include "population.h"
#include <math.h>
#include <stdlib.h>

/**
 * \brief Fonction de rétropropagation du gradient
 * \param reseau
 * Pointeur sur la première couche du réseau
 * \param vecteur_x
 * Tableau des donnée passé en entrée du réseau
 * \param vecteur_y
 * Tableau des donnée attendues en sortie du réseau
 * \param epsilon
 * Valeur permettant de pondérer la considération d'erreur
 * \return Valeur absolue du delta le plus grand obtenu
 */
double backpropagate(Couche *reseau, double *vecteur_x, double *vecteur_y, double epsilon);

/**
 * \brief Fonction qui convertit une couleur en vecteur
 * \param c
 * Couleur a transformer en vecteur
 * \return Tableau de valeur entre 0. et 1.
 */
double* colorToVector(Color c);

/**
 * \brief Fonction qui convertit une vecteur en couleur
 * \param v
 * Vecteur a transformer en couleur
 * \return Couleur créée
 */
Color vectorToColor(double* v);

/**
 * \brief Fonction d'apprentissage selon un jeu de donnée
 * \param reseau
 * Pointeur sur la première couche du réseau
 * \param d
 * Jeu de donnée permettant l'apprentissage
 * \param epsilon
 * Valeur permettant de pondérer la considération d'erreur
 * \param threshold
 * Valeur maximum que le delta doit atteindre pour finir l'apprentissage
 */
void learn(Couche* reseau, Dataset d, double epsilon, double threshold);

/**
 * \brief Fonction de généralisation
 * \param reseau
 * Pointeur sur la première couche du réseau
 * \param image
 * Image dans laquelle on généralise les couleurs des pixels grace au réseau
 */
void generalize(Couche* reseau, Image image);

#endif // BACKPROPAGATION_H
