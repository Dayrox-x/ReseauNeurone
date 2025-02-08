// neuron.h
#ifndef NEURON_H
#define NEURON_H

#define INPUT_SIZE 2 // Nombre d'entrées (x et y)

typedef struct {
    double weights[INPUT_SIZE]; // tableau contenant les poids synaptiques
} Neuron;

double transfer(double x); // Fonction de transfert
double forward(Neuron *neuron, double inputs[INPUT_SIZE]); // calcul de la sortie

