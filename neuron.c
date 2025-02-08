#include "neuron.h"
#include <stdlib.h>
#include <math.h>

// Fonction d'activation : Tangente hyperbolique
double transfer(double x) {
    return tanh(x);
}

// Fonction de propagation avant
double forward(Neuron *neuron, double inputs[INPUT_SIZE]) {
    double sum = 0;
    for (int i = 0; i < INPUT_SIZE; i++) {
        //multiplication des poids par les entrées correspondantes
        sum += neuron->weights[i] * inputs[i];
    }
    return transfer(sum);
}

