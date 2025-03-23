#ifndef NEURON_H
#define NEURON_H

/**
 * \file neuron.h
 * \brief Fonctions de gestion des neurones et réseaux (création, destruction, modification)
 * \author Claire Besançon
 * \author Chloé Legendre Leprêtre
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

/**
 * \struct Neuron
 * \brief Structure d'un neurone
 * 
 * \var Neuron::weights
 * Tableau contenant les poids synaptiques
 * \var Neuron::output
 * Valeur de sortie
 * \var Neuron::delta
 * Écart entre la valeur obtenue et celle attendue
 */
typedef struct {
    double* weights;
    double output;
    double delta;
} Neuron;

/**
 * \struct Couche
 * \brief Structure d'une couche de neurone
 * 
 * \var Couche::tab_n
 * Tableau de neurones
 * \var Couche::next
 * Pointeur vers la couche suivante dans le réseau, NULL si l'on est dans la première couche
 * \var Couche::prev
 * Pointeur vers la couche précédente dans le réseau, NULL si l'on est dans le dernière couche
 * \var Couche::is_fst_couche
 * Indique si l'on est dans la première couche du réseau
 * \var Couche::is_lst_couche
 * Indique si l'on est dans la dernière couche du réseau
 * \var Couche::nb_neurones
 * Nombre de neurones dans la couche
 */
typedef struct Couche {
    Neuron *tab_n;
    struct Couche *next;
    struct Couche *prev;
    bool is_fst_couche;
    bool is_lst_couche;
    int nb_neurones;
} Couche;

/**
 * \brief Fonction de propagation, modifie l'output d'un neurone
 * \param neuron
 * Pointeur sur un neurone
 * \param entree
 * Tableau de neurone de la couche précédente
 * \param nb_synapses
 * Nombre de neurone dans la couche précédente
 */
void forward(Neuron* neuron, Neuron* entree, int nb_synapses);

/**
 * \brief Définit les nouveaux poids synaptiques d'un neurone
 * \param neuron
 * Neurone dont on modifie les poids synaptiques
 * \param new_weights
 * Tableau des nouveaux poids
 * \param nb_synapses
 * Nombre de synapses du neurone
 */
void setWeights(Neuron *neuron, double* new_weights, int nb_synapses);

/**
 * \brief Retourne le poids d'un synapse d'un neurone
 * \param neuron
 * Neurone dont on récupère le poids d'un des synapses
 * \param synapse
 * Position du synapse dans le tableau des poids
 * \return Poids du synapse souhaité
 */
double getWeight(Neuron neuron, int synapse);

/**
 * \brief Définit le nouveau poids du ième synapse d'un neurone
 * \param neuron
 * Pointeur sur le neurone dont on définit le poids d'un des synapses
 * \param i
 * Position du synapse dont on définit la valeur
 * \param new_weight
 * Nouveau poids du synapse
 */
void setWeight(Neuron *neuron, int i, double new_weight);

/**
 * \brief Retourne la valeur en sortie d'un neurone
 * \param neuron
 * Neurone dont on récupère la valeur en sortie
 * \return Valeur en sortie
 */
double getOutputN(Neuron neuron);

/**
 * \brief Retourne la valeur en sortie du ième neurone d'une couche
 * \param couche
 * Pointeur sur la couche de neurone
 * \param i
 * Position du neurone dans la couche
 * \return Valeur en sortie du ième neurone
 */
double getOutputC(Couche *couche, int i);

/**
 * \brief Définit la valeur en sortie d'un neurone
 * \param neuron
 * Pointeur sur le neurone
 * \param new_output
 * Nouvelle valeur en sortie du neurone
 */
void setOutput(Neuron *neuron, double new_output);

/**
 * \brief Retourne la valeur du delta d'un neurone
 * \param neuron
 * Neurone dont on récupère le delta
 * \return Valeur du delta
 */
double getDeltaN(Neuron neuron);

/**
 * \brief Retourne la valeur du delta du ième neurone d'une couche
 * \param couche
 * Pointeur sur la couche de neurone
 * \param i
 * Position du neurone dans la couche
 * \return Valeur du delta
 */
double getDeltaC(Couche *couche, int i);

/**
 * \brief Définit la valeur du delta d'un neurone
 * \param neuron
 * Pointeur sur le neurone
 * \param new_delta
 * Nouvelle valeur du delta
 */
void setDelta(Neuron *neuron, double new_delta);

/**
 * \brief Retourne la ième neurone d'une couche
 * \param couche
 * Pointeur sur la couche
 * \param i
 * Position du neurone dans la couche
 * \return ième neurone dans la couche
 */
Neuron getNeuron(Couche *couche, int i);

/**
 * \brief Place un neurone en ième position dans une couche
 * \param couche
 * Pointeur sur la couche
 * \param i
 * Position du neurone dans la couche
 * \param new_neuron
 * Neurone ajouté a la couche
 */
void setNeuron (Couche *couche, int i, Neuron new_neuron);

/**
 * \brief Retourne le tableau de neurone d'une couche
 * \param couche
 * Pointeur sur la couche dont on récupère le tableau
 * \return Tableau de neurone
 */
Neuron* getNeurons(Couche *couche);

/**
 * \brief Définit le tableau de neurone d'une couche
 * \param couche
 * Pointeur sur la couche dont on définit le tableau
 * \param tab_n
 * Tableau de neurone
 */
void setNeurons(Couche *couche, Neuron *tab_n);

/**
 * \brief Retourne la couche suivante dans le réseau
 * \param currCouche
 * Pointeur sur la couche dont on récupère la couche suivante
 * \return Pointeur sur la couche suivante
 */
Couche* getNextCouche(Couche *currCouche);

/**
 * \brief Définit la couche suivante dans le réseau
 * \param currCouche
 * Pointeur sur la couche dont on définit la couche suivante
 * \param nextCouche
 * Pointeur sur la couche suivante
 */
void setNextCouche(Couche *currCouche, Couche *nextCouche);

/**
 * \brief Retourne la couche précédente dans le réseau
 * \param currCouche
 * Poiteur sur la couche dont on récupère la couche précédente
 * \return Pointeur sur la couche précédente
 */
Couche* getPrevCouche(Couche *currCouche);

/**
 * \brief Définit la couche précédente dans le réseau
 * \param currCouche
 * Pointeur sur la couche dont on définit la couche précédente
 * \param prevCouche
 * Pointeur sur la couche précédente
 */
void setPrevCouche(Couche *currCouche, Couche *prevCouche);

/**
 * \brief Retourne si une couche est la première du réseau ou non
 * \param couche
 * Pointeur sur la couche
 * \return true si c'est la première, false sinon
 */
bool getIsFstCouche(Couche *couche);

/**
 * \brief Définit si une couche est la première du réseau ou non
 * \param couche
 * Pointeur sur la couche
 * \param isFstCouche
 * true si c'est la première, false sinon
 */
void setIsFstCouche(Couche *couche, bool isFstCouche);

/**
 * \brief Retourne si une couche est la dernière du réseau ou non
 * \param couche
 * Pointeur sur la couche
 * \return true si c'est la dernière, false sinon
 */
bool getIsLstCouche(Couche *couche);

/**
 * \brief Définit si une couche est la dernière du réseau ou non
 * \param couche
 * Pointeur sur la couche
 * \param isFstCouche
 * true si c'est la dernière, false sinon
 */
void setIsLstCouche(Couche *couche, bool isLstCouche);

/**
 * \brief Retourne le nombre de neurone dans la couche
 * \param couche
 * Pointeur sur la couche
 * \return Nombre de neurones
 */
int getNbNeurones(Couche *couche);

/**
 * \brief Définit le nombre de neurone dans le couche
 * \param couche
 * Pointeur sur la couche
 * \param nbNeuron
 * Nombre de neurone de la couche
 */
void setNbNeurones(Couche *couche, int nbNeuron);

/**
 * \brief Initialise les valeurs des neurone d'un réseau
 * 
 * Fonction récursive qui initialise tous les neurone d'un réseau jusqu'à la dernière couche
 * 
 * \param curr_couche
 * Pointeur sur la couche actuelle
 * \param nb_synapses
 * Nombre de synapses par neurone de la couche actuelle
 */
void init_neuron(Couche* curr_couche, int nb_synapses);

/**
 * \brief Initialise le tableau de neurones d'une couchec
 * 
 * Fonction qui alloue l'espace mémoire nécessaire au tableau de neurones d'une couche
 * 
 * \param nb_neurones
 * Nombre de neurones de la couche actuelle
 * \param curr_couche
 * Pointeur sur la couche actuelle
 */
void init_tab_neuron(int nb_neurones, Couche* couche);

/**
 * \brief Initialise et retourne une couche de neurone
 * \param nb_neurones
 * Nombre de neurone dans la couche
 * \param couche_suivante
 * Pointeur vers la couche suivante
 * \param couche_prec
 * Pointeur vers la couche précédente
 * \param is_fst_couche
 * true si c'est la première couche du réseau, false sinon
 * \param is_lst_couche
 * true si c'est la dernière couche du réseau, false sinon
 * \return Pointeur sur la couche créée
 */
Couche *init_couche(int nb_neurones, Couche *couche_suivante, Couche* couche_prec, int is_fst_couche, int is_lst_couche);

/**
 * \brief Initialise et retourne un réseau de neurone avec 2 neurones en entrée
 * \param nb_couches
 * Nombre de couches total du réseau
 * \param taille_max
 * Nombre maximal de neurones dans les couches cachées
 * \param taille_min
 * Nombre minimal de neurones dans les couches cachées
 * \param nb_entrees
 * Nombre de synapses par neurones dans la première couche
 * \param nb_sorties
 * Nombre de neurones dans la couche de sortie
 * \return Réseau de neurone
 */
Couche *init_reseau(int nb_couches, int taille_max, int taille_min, int nb_entrees, int nb_sorties);

/**
 * \brief Retourne la dernière couche d'un réseau
 * \param reseau
 * Pointeur sur une couche du réseau
 * \return Pointeur sur la dernière couche du réseau
 */
Couche* getLastCouche(Couche* reseau);

/**
 * \brief Applique la fonction de propagation sur chacun des neurones d'une couche
 * \param couche
 * Pointeur sur la couche
 * \param tab_val
 * Tableau de valeurs en entrée des neurones
 */
void calcul_couche(Couche *couche, Neuron *tab_val);

/**
 * \brief Applique la fonction de propagation sur tout un réseau
 * \param tab_val
 * Tableau de valeur en entrée du réseau
 * \param fst_couche
 * Pointeur sur la première couche du réseau
 */
void calcul_reseau(double *tab_val, Couche *fst_couche);

/**
 * \brief Affiche les poids synaptiques, output et delta de chaque neurone d'une couche
 * \param couche
 * Pointeur sur la couche à afficher
 */
void print_couche(Couche* couche);

/**
 * \brief Affiche couche par couche les poids synaptiques, output et delta de chaque neurone
 * \param reseau
 * Pointeur sur l'une des couche du réseau
 */
void print_reseau(Couche* reseau);

/**
 * \brief Libère l'espace alloué par un neurone
 * \param neuron
 * Neurone dont on libère l'espace
 */
void free_neuron(Neuron neuron);

/**
 * \brief Libère l'espace alloué par une couche
 * \param couche
 * Pointeur sur la couche libérée
 */
void free_tab_neurons(Couche* couche);

/**
 * \brief Libère l'espace alloué par une couche
 * \param couche
 * Pointeur sur la couche libérée
 */
void free_couche(Couche* couche);

/**
 * \brief Libère l'espace alloué par un réseau
 * \param reseau
 * Pointeur sur la première couche du réseau libéré
 */
void free_reseau(Couche* reseau);


#endif // NEURON_H
