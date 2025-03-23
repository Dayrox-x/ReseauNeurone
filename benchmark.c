#include "ubench.h"
#include "neuron.h"
#include "backpropagation.h"
#include "population.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

UBENCH_STATE();

/**********************BENCHMARK INIT RESEAU**********************/
void benchmark_init_reseau() {
    
    int nb_couches = 3;
    int taille_max = 5;
    int taille_min = 3;
    int nb_entrees = 2;
    int nb_sorties = 2;

    Couche* reseau = init_reseau(nb_couches, taille_max, taille_min, nb_entrees, nb_sorties);
    free_reseau(reseau);
}

/********************** BENCHMARK LEARN **********************/
void benchmark_learn() {
    // Paramètres du réseau
    int nb_couches = 3;
    int taille_max = 5;
    int taille_min = 3;
    int nb_entrees = 2;
    int nb_sorties = 2;
    double epsilon = 0.01;  
    double threshold = 0.001; 

    Couche* reseau = init_reseau(nb_couches, taille_max, taille_min, nb_entrees, nb_sorties);
    Dataset d = createDataset();
    createSpiral(d);
    learn(reseau, d, epsilon, threshold);
    free_reseau(reseau);
    destroyDataset(d);
}

/**********************BENCHMARK BACKPROPAGATE**********************/
void benchmark_backpropagation() {
    int nb_couches = 3;
    int taille_max = 5;
    int taille_min = 3;
    int nb_entrees = 2;
    int nb_sorties = 2;
    double epsilon = 0.01; 

    Couche* reseau = init_reseau(nb_couches, taille_max, taille_min, nb_entrees, nb_sorties);
    double vecteur_x[] = {0.5, 0.2};  
    double vecteur_y[] = {0.8, 0.1};  

    calcul_reseau(vecteur_x, reseau);
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

UBENCH_EX(neural_network, learn) {
    UBENCH_DO_BENCHMARK() {
        benchmark_learn();
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
