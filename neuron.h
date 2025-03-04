// neuron.h
#ifndef NEURON_H
#define NEURON_H

#define INPUT_SIZE 2 // Nombre d'entrées (x et y)

typedef struct {
    double* weights; // tableau contenant les poids synaptiques
    double delta //stocke l'erreur de propagation
} Neuron;


typedef struct Couche {
    Neuron *tab_n;        // Tableau de neurones
    struct Couche *p;     // Pointeur vers la couche suivante
    //struct Couche *p;     // Pointeur vers la couche précédente
    int is_fst_couche;    // Indique si c'est la première couche
    int is_lst_couche;    // Indique si c'est la dernière couche
    int nb_neurones;      // Nombre de neurones dans la couche
} Couche;

double transfer(double x); // Fonction de transfert
double forward(Neuron *neuron, double* entree); // calcul de la sortie
void setWeights(Neuron *neuron, double* new_weights);
void init_neuron(Couche* curr_couche, int nb_synapses);
Couche *init_couche(int nb_neurones, Couche *couche_suivante, int is_fst_couche, int is_lst_couche); // Initialisation d'une couche
Couche *init_reseau(int nb_couches, int taille_max, int taille_min, int nb_entrees, int nb_sorties); // Initialisation d'un réseau

double *calcul_couche(Couche *couche, double *tab_val, int input_size); // Calcul de la sortie d'une couche
double *calcul_reseau(double *tab_val, Couche *fst_couche); // Calcul de la sortie d'un réseau


#endif // NEURON_H
