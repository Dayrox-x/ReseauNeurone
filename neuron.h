// neuron.h
#ifndef NEURON_H
#define NEURON_H

#define INPUT_SIZE 2 // Nombre d'entrées (x et y)

typedef struct {
    double weights[INPUT_SIZE]; // tableau contenant les poids synaptiques
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
Couche *init_couche(int nb_neurones, Couche *couche_suivante, int is_fst_couche, int is_lst_couche); // Initialisation d'une couche

#endif // NEURON_H