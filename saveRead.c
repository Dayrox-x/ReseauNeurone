#include <stdio.h>
#include <stdlib.h>
#include "saveRead.h"

#define SORTIE_SEQ ""

void save(Couche *reseau)
{
    // printf("Fonction save() appelée\n");
    // char* sortie_seq;
    // inputNameFicSave(sortie_seq);
    FILE * fichier = fopen(SORTIE_SEQ, "w");
    if (fichier == NULL) {
        printf("Echec de l'ouverture du fichier de sauvegarde\n");
    }
    else{
        Couche *currCouche = reseau;
        while (currCouche != NULL) {
            int nb_neurones = getNbNeurones(currCouche);
            int is_fst_couche = getIsFstCouche(currCouche);
            int is_lst_couche = getIsLstCouche(currCouche);
            int nb_synapse = (getPrevCouche(currCouche) != NULL) ? getNbNeurones(getPrevCouche(currCouche)) : 0;

            fprintf(fichier, "fst_couche : %d lst_couche : %d nb_neurones : %d nb_synapse : %d \n", is_fst_couche, is_lst_couche, nb_neurones, nb_synapse);

            for (int i = 0; i < nb_neurones; i++) {

                Neuron currNeuron = getNeuron(currCouche, i);
                double output = getOutputN(currNeuron);
                double delta = getDeltaN(currNeuron);

                for (int j = 0; j < nb_synapse; j++) {
                    fprintf(fichier, "%lf ;", getWeight(currNeuron, j));
                }

                fprintf(fichier, "%lf %lf \n", output, delta);
            }
            fprintf(fichier, "\n");
            currCouche = getNextCouche(currCouche);
        }

        fclose(fichier);
    }

}


void read(Couche *currCouche) 
{
    // printf("Fonction read() appelée\n");
    // char* sortie_seq;
    // inputNameFicSave(sortie_seq);

    FILE *fichier = fopen(SORTIE_SEQ, "r");
    if (fichier == NULL) {
        printf("Echec de l'ouverture du fichier de sauvegarde\n");
    }

    else{
        Couche *prev = NULL;
        Couche *next = NULL;

        bool theEnd = true;

        while (theEnd) {
            int fst, lst, nb_neurones, nb_synapse;
            if (fscanf(fichier, "fst_couche : %d lst_couche : %d nb_neurones : %d nb_synapse : %d /n", &fst, &lst, &nb_neurones, &nb_synapse) != 4) {
                break; // Fin du fichier ou erreur
            }
            bool is_fst_couche = (fst == 1);
            bool is_lst_couche = (lst == 1);

            setIsFstCouche(currCouche, is_fst_couche);
            setIsLstCouche(currCouche, is_lst_couche);
            setNbNeurones(currCouche, nb_neurones);
            
            if (is_fst_couche) {
                setPrevCouche(currCouche, NULL);
            }
            else{
                setPrevCouche(currCouche, prev);
            }

            free_tab_neurons(currCouche);
            init_tab_neuron(nb_neurones, currCouche);

            Neuron* tab_n = getNeurons(currCouche);

            if (tab_n == NULL) {
                fprintf(stderr, "Erreur d'allocation mémoire pour les neurones.\n");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < nb_neurones; i++) {

                init_neuron(currCouche, nb_synapse);

                Neuron currNeuron = getNeuron(currCouche, i);
                
                

                for (int j = 0; j < nb_synapse; j++) {
                    double weight = getWeight(currNeuron, j);
                    fscanf(fichier, "%lf ;", &weight);
                    setWeight(getNeurons(currCouche), j, weight);
                }

                double output, delta;
                fscanf(fichier, "%lf %lf \n", &output, &delta);
                setOutput(&currNeuron, output);
                setDelta(&currNeuron, delta);
            }

            fscanf(fichier, "\n");
            setNeurons(currCouche, tab_n);

            prev = currCouche;

            if (is_lst_couche) {
                setNextCouche(currCouche, next);
                theEnd = false;
            }
            else{
                currCouche = getNextCouche(currCouche);
            }

            if (currCouche == NULL) {
                fprintf(stderr, "Erreur d'allocation mémoire pour une nouvelle couche.\n");
                exit(EXIT_FAILURE);
            }
        }

        fclose(fichier);
    }
    
}
