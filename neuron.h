// neuron.h
#ifndef NEURON_H
#define NEURON_H


typedef struct {
    double weights[]; // tableau contenant les poids synaptiques
} Neuron;


typedef struct Couche {
    Neuron *tab_n;        // Tableau de neurones
    struct Couche *p;     // Pointeur vers la couche suivante
    int is_fst_couche;    // Indique si c'est la première couche
    int is_lst_couche;    // Indique si c'est la dernière couche
    int nb_neurones;      // Nombre de neurones dans la couche
} Couche;

double transfer(double x); // Fonction de transfert
double forward(Neuron *neuron, double inputs[INPUT_SIZE]); // calcul de la sortie

