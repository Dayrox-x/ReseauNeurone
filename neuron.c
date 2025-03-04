#include "neuron.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



// Fonction de transfert : Tangente hyperbolique
double transfer(double x) {
    return tanh(x);
}

double set_nbTab(Neuron *neuron) {
    int len = 0
    while (neuron.weigts[len] != NULL){
        len++;
    }
    return len;
}

// Fonction de propagation 
double forward(Neuron *neuron, double* entree) {
    double sum = 0;
    for (int i = 0; i < set_nbSynapse(Neuron); i++) {
        sum += neuron->weights[i] * entree[i];
    }
    return transfer(sum);
}

// Fonction pour modifier la valeur des poids d'un neurone
void setWeights(Neuron *neuron, double* new_weights) {
    for (int i = 0; i < set_nbSynapse(Neuron); i++) {
        neuron->weights[i] = new_weights[i];
    }
}

void init_neuron(Couche* curr_couche, int nb_synapses){
    if (curr_couche.p != NULL)
    {
        for (int i = 0; i < nb_neurones; i++) {
            for (int j = 0; j < nb_synapse; j++) {
                couche->tab_n[i].weights[j] = ((double)rand() / RAND_MAX) * 2 - 1; 
            }
        }
        init_neuron(curr_couche.p, curr_couche.nb_neurones);
    }
}

// Initialisation d'une couche
Couche *init_couche(int nb_neurones, Couche *couche_suivante, int is_fst_couche, int is_lst_couche) {
    Couche *couche = malloc(sizeof(Couche));
    if (!couche) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }

    couche->nb_neurones = nb_neurones;
    couche->tab_n = malloc(nb_neurones * sizeof(Neuron));
    if (!couche->tab_n) {
        printf("Erreur d'allocation mémoire\n");
        free(couche);
        exit(1);
    }

    couche->p = couche_suivante;
    couche->is_fst_couche = is_fst_couche;
    couche->is_lst_couche = is_lst_couche;

    return couche;
}


Couche *init_reseau(int nb_couches, int taille_max, int taille_min, int nb_entrees, int nb_sorties) {
	// creation couche de sortie (nb_sorties = nb_neurones)
    Couche *lst_couche = init_couche(nb_sorties, NULL, 0, 1);
    Couche *temp = lst_couche;
	// ajout des couches cachées (leurs nb de neurones est aléatoire)
    for (int i = 1; i < nb_couches - 1; i++) {
        int taille_courante = rand() % (taille_max - taille_min + 1) + taille_min;
        //chaque nouvelle couche pointe vers la précédente
        temp = init_couche(taille_courante, temp, 0, 0);
    }
    Couche *fst_couche = init_couche(nb_entrees, temp, 1, 0);
    init_neuron(fst_couche, nb_entrees);
    return fst_couche;
}



double *calcul_couche(Couche *couche, double *tab_val, int input_size) {
	//allocation du tab qui stocke la sortie de chaque neurone de la couche
    double *tab_result = malloc(couche->nb_neurones * sizeof(double));
    if (!tab_result) {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
		
	//pour chaque neurone on applique la fonction de propagation
    for (int i = 0; i < couche->nb_neurones; i++) {
        tab_result[i] = forward(&couche->tab_n[i], tab_val);
    }
    return tab_result;
}


double *calcul_reseau(double *tab_val, Couche *fst_couche) {
    Couche *current = fst_couche;
    double *result = tab_val; 
    while (current) { // tant qu'on n'est pas à la dernière couche => sorties deviennent les entrées de couche suivante.
        result = calcul_couche(current, result, INPUT_SIZE); //stocke tempo les sorties de chaque couche avant d’être transmises à suivante
        current = current->p;
    }
    return result;
}

void interpretation(double *tab_val_sortie, char *tab_sortie[], int len) {
    for (int i = 0; i < len; i++) {
        printf("Le point a une probabilité de %f d’être %s\n", tab_val_sortie[i], tab_sortie[i]);
    }
}

// faire les free dans une fonction


