#include <stdio.h>
#include <stdlib.h>
#include "save.h"

#define SORTIE_SEQ "partieseq.cls"

void save(Couche *reseau)
{
    FILE * fichier = fopen(SORTIE_SEQ, "w");
    if (fichier == NULL) {
        printf("Echec de l'ouverture du fichier de sauvegarde\n");
        return;
    }

    Couche *currCouche = reseau;
    while (currCouche != NULL) {
        int nb_neurones = getNbNeurones(currCouche);
        int is_fst_couche = getIsFstCouche(currCouche);
        int is_lst_couche = getIsLstCouche(currCouche);
        int nb_synapse = (getPrevCouche(currCouche) != NULL) ? getNbNeurones(getPrevCouche(currCouche)) : 0;

        fprintf(fichier, "%d %d %d %d ", is_fst_couche, is_lst_couche, nb_neurones, nb_synapse);

        for (int i = 0; i < nb_neurones; i++) {
            Neuron currNeuron = getNeuron(currCouche, i);
            double output = getOutputN(currNeuron);
            double delta = getDeltaN(currNeuron);

            for (int j = 0; j < nb_synapse; j++) {
                fprintf(fichier, "%lf ", getWeight(currNeuron, j));
            }

            fprintf(fichier, "%lf %lf ", output, delta);
        }

        currCouche = getNextCouche(currCouche); // ✅ Avance dans la liste des couches
    }

    fclose(fichier);
}


void read(Couche *currCouche) {
    FILE *fichier = fopen(SORTIE_SEQ, "r");
    if (fichier == NULL) {
        printf("Echec de l'ouverture du fichier de sauvegarde\n");
        return;
    }

    Couche *prev = NULL;
    Couche *next = NULL;

    while (1) {
        int fst, lst, nb_neurones, nb_synapse;
        if (fscanf(fichier, "%d %d %d %d", &fst, &lst, &nb_neurones, &nb_synapse) != 4) {
            break; // Fin du fichier ou erreur
        }

        bool is_fst_couche = (fst == 1);
        bool is_lst_couche = (lst == 1);

        setIsFstCouche(currCouche, is_fst_couche);
        setIsLstCouche(currCouche, is_lst_couche);
        setNbNeurones(currCouche, nb_neurones);
        setPrevCouche(currCouche, prev);
        if (prev != NULL) {
            setNextCouche(prev, currCouche);
        }

        Neuron* tab_n = malloc(nb_neurones * sizeof(Neuron));
        if (tab_n == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour les neurones.\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < nb_neurones; i++) {
            double* weights = malloc(nb_synapse * sizeof(double));
            if (weights == NULL) {
                fprintf(stderr, "Erreur d'allocation mémoire pour les poids.\n");
                exit(EXIT_FAILURE);
            }

            for (int j = 0; j < nb_synapse; j++) {
                fscanf(fichier, "%lf", &weights[j]);
            }

            init_neuron(currCouche, nb_synapse); // Si tu as une fonction pour initialiser un neurone
            setWeights(getNeurons(currCouche), weights, nb_synapse);

            double output, delta;
            fscanf(fichier, "%lf %lf", &output, &delta);
            setOutput(&tab_n[i], output);
            setDelta(&tab_n[i], delta);

            free(weights); // Libération immédiate après copie dans le neurone
        }

        setNeurons(currCouche, tab_n);

        prev = currCouche;
        if (is_lst_couche) {
            setNextCouche(currCouche, next);
            break;
        }

        currCouche = malloc(sizeof(Couche)); // On alloue une nouvelle couche pour la prochaine itération
        if (currCouche == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour une nouvelle couche.\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(fichier);
}
