#include "backpropagation.h"

// Fonction de rétropropagation du gradient
double backpropagate(Couche *reseau, double *vecteur_x, double *vecteur_y, double epsilon) {
    // 1. Propagation de l'exemple à travers le réseau pour obtenir les sorties
    calcul_reseau(vecteur_x, reseau);
    double max_delta = 0.;

    // 2. Calcul des deltas pour la couche de sortie
    int nb_couches = 1;
    Couche* last = reseau;
    while (!last->is_lst_couche) { // acces a la derniere couche du reseau + comptage du nombre de couche
        last = last->next;
        nb_couches++;
    }

    for (int i = 0; i < last->nb_neurones; i++) {
        last->tab_n[i].delta = (1 - last->tab_n[i].output * last->tab_n[i].output) * (vecteur_y[i] - last->tab_n[i].output);
        if (last->tab_n[i].delta - max_delta > 0.) {
            max_delta = last->tab_n[i].delta;
        }
    }

    // 3. Propagation des deltas à travers les couches cachées (de la dernière à la première)
    Couche* curr = last->prev;
    for (int q = nb_couches-1; q > 1; q--) {
        for (int i = 0; i < curr->nb_neurones; i++) {
            double sum = 0.;
            for (int k = 0; k < last->nb_neurones; k++) {
                sum += last->tab_n[k].delta * last->tab_n[k].weights[i];
            }
            curr->tab_n[i].delta = (1 - curr->tab_n[i].output * curr->tab_n[i].output) * sum;
            if (curr->tab_n[i].delta - max_delta > 0.) {
                max_delta = curr->tab_n[i].delta;
            }
        }
        curr = curr->prev;
        last = last->prev;
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
    v[0] = (double)getR(c) / 255.0;
    v[1] = (double)getB(c) / 255.0;
    return v;
}

Color vectorToColor(double* v){
    int r, g, b;
    r = (int)(v[0] * 255.0);
    g = 0.;
    b = (int)(v[1] * 255.0);
    return createColor(r, g, b, 255.0);
}

void learn(Couche* reseau, Dataset d, double epsilon, double threshold) {
    double di_max = threshold;
    double* v_x = malloc(sizeof(double) * 2);
    double* v_y;
    int i = 0;
    int iteration = 0;

    while (di_max - threshold >= 0.) {
        i = (i+1) % getDatasetSize(d);
        int x = getX(getDatasetPixel(d, i));
        int y = getY(getDatasetPixel(d, i));
        v_x[0] = (float)x + 1.;
        v_x[1] = (float)y + 1.;
        v_y = colorToVector(getColor(getDatasetPixel(d, i)));
        di_max = backpropagate(reseau, v_x, v_y, epsilon);
        free(v_y);

        // Log de la progression
        iteration++;
        if (iteration % 1000 == 0) {
            printf("Iteration %d, di_max: %f\n", iteration, di_max);
        }
    }

    printf("Learning completed in %d iterations with final di_max: %f\n", iteration, di_max);
    free(v_x);
}

void generalize(Couche* reseau, Image image){
    int x = rand() % getWidth(image);
    int y = rand() % getHeight(image);
    double* v = malloc(sizeof(double) * 2);
    v[0] = (double)x + 1.;
    v[1] = (double)y + 1.;
    calcul_reseau(v, reseau);

    Couche* last = getLastCouche(reseau);
    double* outputs = malloc(sizeof(double) * last->nb_neurones);
    for (int i = 0; i < last->nb_neurones; i++){
        outputs[i] = last->tab_n[i].output;
    }
    Color c = vectorToColor(outputs);
    
    setPixelColor(image, x, y, c);

    free(v);
    free(outputs);
    destroyColor(c);
}