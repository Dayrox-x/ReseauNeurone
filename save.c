#include <stdio.h>
#include <stdlib.h>
#include "save.h"

#define SORTIE_SEQ "partieseq.cls"

void save(Couche *reseau)
{
    FILE * fichier = fopen(SORTIE_SEQ,"w");

    if(fichier == NULL)
    {
        printf("Echec de l ouverture du fichier de sauvegarde\n");
    }else
    {
        Couche *currCouche = reseau;
        Neuron currNeuron;
        Couche *next, *prev;
        bool is_fst_couche, is_lst_couche;
        int nb_neurones, nb_synapse;

        double weight;
        double output;
        double delta;


        while(currCouche != NULL){
            //Rmq on ne doit pas stocker les pointeurs uniquement leur contenus non?
            nb_neurones = getNbNeurones(currCouche);
            is_fst_couche = getIsFstCouche(currCouche);
            is_lst_couche = getIsLstCouche(currCouche);

            prev = getPrevCouche(currCouche);
            nb_synapse = getNbNeurones(prev);

            fprintf(fichier, "%d %d %d %d", is_fst_couche, is_lst_couche, nb_neurones, nb_synapse);

            for (int i = 0; i < nb_neurones; i++){
                currNeuron = getNeuron(currCouche, i);
                output = getOutputN(currNeuron);
                delta = getDeltaN(currNeuron);

                for (int j = 0; j < nb_synapse; j++){
                    weight = getWeight(currNeuron, j);
                    fprintf(fichier, "%d ", weight);
                }

                fprintf(fichier, "%d %d", output, delta);
            }

        }
    }
        
}

void read(Couche *reseau) {
    FILE *fichier = fopen(SORTIE_SEQ, "r");

    if (fichier == NULL) {
        printf("Echec de l'ouverture du fichier de sauvegarde\n");
        return;
    }


    Couche *currCouche;
    Neuron *currNeuron;
    Couche *next, *prev;
    bool is_fst_couche, is_lst_couche;
    int nb_neurones, nb_synapse;

    double weight;
    double output;
    double delta;

    prev = NULL;
    next = NULL;

    bool theEnd = true;

    reseau = currCouche;

    while (theEnd){
        fscanf(fichier, "%d %d %d %d", &is_fst_couche, &is_lst_couche, &nb_neurones, &nb_synapse);
    
        setIsFstCouche(currCouche, is_fst_couche);
        setIsLstCouche(currCouche, is_lst_couche);
        setNbNeurones(currCouche, nb_neurones);
        setPrevCouche(currCouche, prev);
        if (!is_fst_couche){
            setNextCouche(prev, &currCouche);
        }

        Neuron tab_n[nb_neurones];
        for (int i = 0; i < nb_neurones; i++){
            double weights[nb_synapse];
            for(int j = 0; j < nb_synapse; j++){
                fscanf(fichier, "%d", &weight);
                weights[j] = weight;
            }
            currNeuron = &tab_n[i];
            setWeights(currNeuron, weights, nb_synapse);
            fscanf(fichier, "%d %d", &output, &delta);
            setOutput(currNeuron, output);
            setDelta(currNeuron, delta);
        }
        setNeurons(&currCouche, tab_n);
        prev = &currCouche;
        if(is_lst_couche){
            setNextCouche(currCouche, NULL);
            theEnd = !theEnd;
        }
    }

    fclose(fichier);
}
