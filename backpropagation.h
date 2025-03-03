#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "neuron.h"

// Fonction de rétropropagation du gradient
void backpropagate(Couche *reseau, double *vecteur_x, double *vecteur_y, double epsilon);

#endif // BACKPROPAGATION_H
