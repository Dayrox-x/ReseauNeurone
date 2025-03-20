#include "ubench.h"
#include "neuron.h"
#include "backpropagation.h"
#include "population.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

UBENCH_STATE();

/**********************BENCHMARK INIT RESEAU**********************/
// Fonction pour initialiser un réseau de neurones
void benchmark_init_reseau() {
    
    int nb_couches = 3;
    int taille_max = 5;
    int taille_min = 3;
    int nb_entrees = 2;
    int nb_sorties = 2;

    Couche* reseau = init_reseau(nb_couches, taille_max, taille_min, nb_entrees, nb_sorties);
    free_reseau(reseau);
}

/**********************BENCHMARK BACKPROPAGATE**********************/
// Fonction pour générer un réseau et effectuer la rétropropagation
void benchmark_backpropagation() {
    // Initialiser un réseau de neurones
    int nb_couches = 3;
    int taille_max = 5;
    int taille_min = 3;
    int nb_entrees = 2;
    int nb_sorties = 2;
    double epsilon = 0.01; // Taux d'apprentissage

    // Créer un réseau avec les spécifications données
    Couche* reseau = init_reseau(nb_couches, taille_max, taille_min, nb_entrees, nb_sorties);

    // Exemple de données d'entrée pour le réseau et de données cibles (target)
    double vecteur_x[] = {0.5, 0.2};  // Entrée du réseau
    double vecteur_y[] = {0.8, 0.1};  // Sortie cible 

    calcul_reseau(vecteur_x, reseau);

    // Calcul de la rétropropagation 
    backpropagate(reseau, vecteur_x, vecteur_y, epsilon);
    free_reseau(reseau);
}
/**********************BENCHMARK CALCUL RESEAU**********************/

void benchmark_calcul_reseau() {
    int nb_couches = 3;
    int taille_max = 5;
    int taille_min = 3;
    int nb_entrees = 2;
    int nb_sorties = 2;

    Couche* reseau = init_reseau(nb_couches, taille_max, taille_min, nb_entrees, nb_sorties);

    // Exemple de données d'entrée pour le réseau
    double vecteur_x[] = {0.5, 0.2};
    calcul_reseau(vecteur_x, reseau);
    free_reseau(reseau);
}

// Définition du benchmark
UBENCH_EX(neural_network, init_reseau) {
    UBENCH_DO_BENCHMARK() {
        benchmark_init_reseau();
    }
}

UBENCH_EX(neural_network, calcul_reseau) {
    UBENCH_DO_BENCHMARK() {
        benchmark_calcul_reseau();
    }
}

UBENCH_EX(neural_network, backpropagation) {
    UBENCH_DO_BENCHMARK() {
        benchmark_backpropagation();
    }
}

int main(int argc, const char* const argv[]) {
    // Exécution des benchmarks
    return ubench_main(argc, argv);
}
