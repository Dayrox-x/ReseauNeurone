#include "neuron.h"
#include "population.h"
#include <math.h>
#include <stdlib.h>

// Fonction de rétropropagation du gradient
double backpropagate(Couche *reseau, double *vecteur_x, double *vecteur_y, double epsilon) {
    // 1. Propagation de l'exemple à travers le réseau pour obtenir les sorties
    double *sortie = calcul_reseau(vecteur_x, reseau);
    double max_delta = 0.;

    // 2. Calcul des deltas pour la couche de sortie
    int nb_couches = 1;
    Couche* last = reseau;
    while (!last->is_lst_couche) { // acces a la derniere couche du reseau + comptage du nombre de couche
        last = last->next;
        nb_couches++;
    }
    for (int i = 0; i < last->nb_neurones; i++) {
        last->tab_n[i].delta = (1 - sortie[i] * sortie[i]) * (vecteur_y[i] - sortie[i]);
        if (last->tab_n[i].delta > max_delta) {
            max_delta = last->tab_n[i].delta;
        }
    }

    // 3. Propagation des deltas à travers les couches cachées (de la dernière à la première)
    Couche* curr = last->prev;
    for (int q = nb_couches-1; q > 0; q--) {
        for (int i = 0; i < curr->nb_neurones; i++) {
            double sum = 0.;
            for (int k = 0; k < last->nb_neurones; k++) {
                sum += last->tab_n[k].delta * last->tab_n[k].weights[i];
            }
            curr->tab_n[i].delta = (1 - curr->tab_n[i].output * curr->tab_n[i].output) * sum;
            if (curr->tab_n[i].delta > max_delta) {
                max_delta = curr->tab_n[i].delta;
            }
            curr = curr->prev;
            last = last->prev;
        }
    }

    // 4. Mise à jour des poids
    last = curr;
    curr = curr->next;

    while (curr) {
        for (int i = 0; i < curr->nb_neurones; i++) {
            for (int j = 0; j < last->nb_neurones; j++) {
                curr->tab_n[i].weights[j] += epsilon * curr->tab_n[i].delta * last->tab_n[j].output;
            }
        }
        curr = curr->next;
        last = last->next;
    }

    return max_delta;
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