#include "neuron.h"
#include "population.h"
#include <math.h>
#include <stdlib.h>

// Fonction de rétropropagation du gradient
double backpropagate(Couche *reseau, double *vecteur_x, double *vecteur_y, double epsilon) {
    // 1. Propagation de l'exemple à travers le réseau pour obtenir les sorties
    double *sortie = calcul_reseau(vecteur_x, reseau);  
    double max_di = 0;

    // 2. Calcul des deltas pour la couche de sortie
    // Pour chaque neurone de la couche de sortie
    for (int i = 0; i < reseau->p->nb_neurones; i++) {
        double si = sortie[i];  // Sortie calculée du neurone i
        double yi = vecteur_y[i];  // Valeur attendue pour ce neurone
        double di = (1 - si * si) * (yi - si);  // Calcul du delta pour le neurone i
        reseau->p->tab_n[i].delta = di;  // Sauvegarde du delta dans le neurone
        if (di > max_di) {
            max_di = di ;
        }
    }

    // 3. Propagation des deltas à travers les couches cachées (de la dernière à la première)
    for (Couche *current = reseau->p; current != NULL; current = current->p) {
        for (int i = 0; i < current->nb_neurones; i++) {
            Neuron *neurone = &current->tab_n[i];
            double oi = neurone->sortie;  // Sortie calculée du neurone i de la couche cachée

            // Calcul du delta pour chaque neurone caché
            double somme_deltas = 0;
            for (int k = 0; k < current->p->nb_neurones; k++) {
                somme_deltas += current->p->tab_n[k].delta * current->p->tab_n[k].weights[i];
            }
            neurone->delta = (1 - oi * oi) * somme_deltas;  // Calcul du delta pour le neurone i
        }
    }

    // 4. Mise à jour des poids
    for (Couche *current = reseau; current != NULL; current = current->p) {
        for (int i = 0; i < current->nb_neurones; i++) {
            Neuron *neurone = &current->tab_n[i];
            for (int j = 0; j < INPUT_SIZE; j++) {
                double x_ij = vecteur_x[j];  // Entrée du neurone
                double new_weight = neurone->weights[j] + epsilon * neurone->delta * x_ij;
                // Mise à jour des poids
                neurone->weights[j] = new_weight;
            }
        }
    }
    return max_di;
}

double* colorToVector(Color c) {
    double* v = malloc(sizeof(double) * 2);
    if (getR(c) == 255){ // rouge = [1., 0.] et bleu = [0., 1.]
        v[0] = 1.;
        v[1] = 0.;
    } else {
        v[0] = 0.;
        v[1] = 1.;
    }
    return v;
}

void learn(Couche* reseau, Image img, double epsilon, double threshold) {
    double di_max = threshold;
    double* v_x = malloc(sizeof(double) * 2);
    double* v_y;
    while (di_max >= threshold) {
        int x = rand()/getWidth(img);
        int y = rand()/getHeight(img);
        v_x[0] = (float)x;
        v_x[1] = (float)y;
        v_y = colorToVector(getPixelColor(img, x, y));
        di_max = backpropagate(reseau, v_x, v_y, epsilon);
        free(v_y);
    }
    free(v_x);
}