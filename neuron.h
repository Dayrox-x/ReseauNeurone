// neuron.h
#ifndef NEURON_H
#define NEURON_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

//#define INPUT_SIZE 2 // Nombre d'entrées (x et y)

typedef struct {
    double* weights; // tableau contenant les poids synaptiques
    double output;
    double delta;
} Neuron;


typedef struct Couche {
    Neuron *tab_n;        // Tableau de neurones
    struct Couche *next;     // Pointeur vers la couche suivante
    struct Couche *prev;     // Pointeur vers la couche précédente
    bool is_fst_couche;    // Indique si c'est la première couche
    bool is_lst_couche;    // Indique si c'est la dernière couche
    int nb_neurones;      // Nombre de neurones dans la couche
} Couche;

double transfer(double x); // Fonction de transfert
void forward(Neuron* neuron, Neuron* entree, int nb_synapses); // calcul de la sortie
void setWeights(Neuron *neuron, double* new_weights, int nb_synapses);
void init_neuron(Couche* curr_couche, int nb_synapses);
Couche *init_couche(int nb_neurones, Couche *couche_suivante, Couche* couche_prec, int is_fst_couche, int is_lst_couche); // Initialisation d'une couche
Couche *init_reseau(int nb_couches, int taille_max, int taille_min, int nb_entrees, int nb_sorties); // Initialisation d'un réseau

void calcul_couche(Couche *couche, Neuron *tab_val); // Calcul de la sortie d'une couche
void calcul_reseau(double *tab_val, Couche *fst_couche); // Calcul de la sortie d'un réseau

void print_reseau(Couche* reseau);

#endif // NEURON_H
