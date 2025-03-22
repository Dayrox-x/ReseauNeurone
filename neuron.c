#include "neuron.h"

// Fonction de propagation 
void forward(Neuron* neuron, Neuron* entree, int nb_synapses) {
    double sum = 0;
    for (int i = 0; i < nb_synapses; i++) {
        sum += neuron->weights[i] * entree[i].output;
    }
    neuron->output = tanh(sum);
}

// Fonction pour modifier la valeur des poids d'un neurone
void setWeights(Neuron *neuron, double* new_weights, int nb_synapses) {
    for (int i = 0; i < nb_synapses; i++) {
        setWeight(neuron, i, new_weights[i]);
    }
}

double getWeight(Neuron neuron, int synapse) {
    return neuron.weights[synapse];
}

void setWeight(Neuron *neuron, int i, double new_weight){
    neuron->weights[i] = new_weight;
}

double getWeightC(Couche *couche, int neurone, int synapse){
    return getWeight(getNeuron(couche, neurone), synapse);
}

double getOutputN(Neuron neuron){
    return neuron.output;
}

double getOutputC(Couche *couche, int i){
    return getOutputN(getNeuron(couche, i));
}

void setOutput(Neuron *neuron, double new_output){
    neuron->output = new_output;
}

double getDeltaN(Neuron neuron){
    return neuron.delta;
}

double getDeltaC(Couche *couche, int i){
    return getDeltaN(getNeuron(couche, i));
}

void setDelta(Neuron *neuron, double new_delta){
    neuron->delta = new_delta;
}

Neuron getNeuron(Couche *couche, int i){
    return couche->tab_n[i];
}

void setNeuron (Couche *couche, int i, Neuron new_neuron){
    couche->tab_n[i] = new_neuron;
}

Neuron* getNeurons(Couche *couche){
    return couche->tab_n;
}

void setNeurons(Couche *couche, Neuron *tab_n){
    couche->tab_n = tab_n;
}

Couche* getNextCouche(Couche *currCouche){
    return currCouche->next;
}

void setNextCouche(Couche *currCouche, Couche *nextCouche){
    currCouche->next = nextCouche;
}

Couche* getPrevCouche(Couche *currCouche){
    return currCouche->prev;
}

void setPrevCouche(Couche *currCouche, Couche *prevCouche){
    currCouche->prev = prevCouche;
}

bool getIsFstCouche(Couche *couche){
    return couche->is_fst_couche;
}

void setIsFstCouche(Couche *couche, bool isFstCouche){
    couche->is_fst_couche = isFstCouche;
}

bool getIsLstCouche(Couche *couche){
    return couche->is_lst_couche;
}

void setIsLstCouche(Couche *couche, bool isLstCouche){
    couche->is_lst_couche = isLstCouche;
}

int getNbNeurones(Couche *couche){
    return couche->nb_neurones;
}

void setNbNeurones(Couche *couche, int nbNeuron){
    couche->nb_neurones = nbNeuron;
}

void init_neuron(Couche* curr_couche, int nb_synapses){
    if (curr_couche != NULL)
    {
        for (int i = 0; i < curr_couche->nb_neurones; i++) {
            curr_couche->tab_n[i].weights = malloc(sizeof(double) * nb_synapses);
            for (int j = 0; j < nb_synapses; j++) {
                double weight;
                double range = curr_couche->is_lst_couche ? 1.0 : sqrt(6.0 / (curr_couche->nb_neurones + curr_couche->next->nb_neurones));
                weight = curr_couche->is_fst_couche ? 1.0 : ((double)rand() / (double)RAND_MAX) * 2. * range - range;
                curr_couche->tab_n[i].weights[j] = weight;
                curr_couche->tab_n[i].output = 0.0;
                curr_couche->tab_n[i].delta = 0.0;
            }
        }
        init_neuron(curr_couche->next, curr_couche->nb_neurones);
    }
}

// Initialisation d'une couche
Couche *init_couche(int nb_neurones, Couche *couche_suivante, Couche* couche_prec, int is_fst_couche, int is_lst_couche) {
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

    couche->next = couche_suivante;
    couche->prev = couche_prec;
    couche->is_fst_couche = is_fst_couche;
    couche->is_lst_couche = is_lst_couche;

    return couche;
}


Couche *init_reseau(int nb_couches, int taille_max, int taille_min, int nb_entrees, int nb_sorties) {
	// creation couche de sortie (nb_sorties = nb_neurones)
    Couche *lst_couche = init_couche(nb_sorties, NULL, NULL, false, true);
    Couche *temp = lst_couche;
    Couche *previous = lst_couche;
    srand(time(NULL));
	// ajout des couches cachées (leurs nb de neurones est aléatoire)
    for (int i = 1; i < nb_couches - 1; i++) {
        int taille_courante = rand() % (taille_max - taille_min + 1) + taille_min;
        //chaque nouvelle couche pointe vers la précédente
        temp = init_couche(taille_courante, temp, NULL, false, false);
        previous->prev = temp;
        previous = temp;
    }
    Couche *fst_couche = init_couche(nb_entrees, temp, NULL, true, false);
    previous->prev = fst_couche;
    init_neuron(fst_couche, 1);
    return fst_couche;
}

Couche* getLastCouche(Couche* reseau){
    Couche* last = reseau;
    while (!last->is_lst_couche) { // acces a la derniere couche du reseau + comptage du nombre de couche
        last = last->next;
    }
    return last;
}


void calcul_couche(Couche *couche, Neuron *tab_n) {
	//pour chaque neurone on applique la fonction de propagation
    for (int i = 0; i < getNbNeurones(couche); i++) {
        forward(&(couche->tab_n[i]), tab_n, getNbNeurones(getPrevCouche(couche)));
    }
}


void calcul_reseau(double *tab_val, Couche *fst_couche) {
    for (int i = 0; i < fst_couche->nb_neurones; i++) { // on part du principe que c'est effectivement la premiere couche
        fst_couche->tab_n[i].output = tab_val[i];
    }
    Couche *current = fst_couche->next;
    while (current) { // tant qu'on n'est pas à la dernière couche => sorties deviennent les entrées de couche suivante.
        calcul_couche(current, current->prev->tab_n); //stocke tempo les sorties de chaque couche avant d’être transmises à suivante
        current = current->next;
    }
}

void print_couche(Couche* couche) {
    for (int i = 0; i < couche->nb_neurones; i++) {
        printf("   Neurone %d : \n", i+1);
        int nb_synapses = 1;
        if (couche->prev != NULL) {
            nb_synapses = couche->prev->nb_neurones;
        }
        for (int j = 0; j < nb_synapses; j++){
            printf("      Poids synapse %d : %lf\n", j+1, couche->tab_n[i].weights[j]);
        }
        printf("      Output : %lf\n      Delta : %lf\n", couche->tab_n[i].output, couche->tab_n[i].delta);
    }
}

void print_reseau(Couche* reseau) {
    Couche* curr = reseau;
    while(!curr->is_fst_couche) {
        curr = curr->prev;
    }

    int i = 1;
    while(curr != NULL) {
        printf("Couche %d : [is_fst_couche : %d ; is_lst_couche : %d ; nb_neurones : %d]\n", i, curr->is_fst_couche, curr->is_lst_couche, curr->nb_neurones);
        i++;
        print_couche(curr);
        curr = curr->next;
    }
}


// Fonctions de liberation de mémoire
// on free le neuron, la couche, et l'ensemble du reseau

void free_neuron(Neuron neuron) {
    if (neuron.weights != NULL) {
        free(neuron.weights);
        neuron.weights = NULL;
    }
}

void free_couche(Couche* couche) {
    if (couche != NULL) {
        for (int i = 0; i < couche->nb_neurones; i++) {
            free_neuron(couche->tab_n[i]);
        }
        free(couche->tab_n);
        couche->tab_n = NULL;

        free(couche);
        couche = NULL;
    }
}

void free_reseau(Couche* reseau) {
    if (reseau != NULL) {
        Couche* next = reseau->next;
        free_couche(reseau);
        free_reseau(next);
    }
}


