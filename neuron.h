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

double getWeight(Neuron neuron, int synapse);
void setWeight(Neuron *neuron, int i, double new_weight);
double getOutputN(Neuron neuron);
double getOutputC(Couche *couche, int i);
void setOutput(Neuron *neuron, double new_output);
double getDeltaN(Neuron neuron);
double getDeltaC(Couche *couche, int i);
void setDelta(Neuron *neuron, double new_delta);
Neuron getNeuron(Couche *couche, int i);
void setNeuron (Couche *couche, int i, Neuron new_neuron);
Neuron* getNeurons(Couche *couche);
void setNeurons(Couche *couche, Neuron *tab_n);
Couche* getNextCouche(Couche *currCouche);
void setNextCouche(Couche *currCouche, Couche *nextCouche);
Couche* getPrevCouche(Couche *currCouche);
void setPrevCouche(Couche *currCouche, Couche *prevCouche);
bool getIsFstCouche(Couche *couche);
void setIsFstCouche(Couche *couche, bool isFstCouche);
bool getIsLstCouche(Couche *couche);
void setIsLstCouche(Couche *couche, bool isLstCouche);
int getNbNeurones(Couche *couche);
void setNbNeurones(Couche *couche, int nbNeuron);

void init_neuron(Couche* curr_couche, int nb_synapses);
Couche *init_couche(int nb_neurones, Couche *couche_suivante, Couche* couche_prec, int is_fst_couche, int is_lst_couche); // Initialisation d'une couche
Couche *init_reseau(int nb_couches, int taille_max, int taille_min, int nb_entrees, int nb_sorties); // Initialisation d'un réseau

Couche* getLastCouche(Couche* reseau); // renvoie la derniere couche d'un reseau

void calcul_couche(Couche *couche, Neuron *tab_val); // Calcul de la sortie d'une couche
void calcul_reseau(double *tab_val, Couche *fst_couche); // Calcul de la sortie d'un réseau

void print_reseau(Couche* reseau);

void free_reseau(Couche* reseau);

#endif // NEURON_H
