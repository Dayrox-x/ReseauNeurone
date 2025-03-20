#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "neuron.h"
#include "population.h"
#include <math.h>
#include <stdlib.h>

// Fonction de rétropropagation du gradient
double backpropagate(Couche *reseau, double *vecteur_x, double *vecteur_y, double epsilon);

// Fonction qui convertit une couleur en vecteur
double* colorToVector(Color c);

// Fonction qui permet l'apprentissage des neurones 
void learn(Couche* reseau, Dataset d, double epsilon, double threshold);

void generalize(Couche* reseau, Image image);

#endif // BACKPROPAGATION_H
