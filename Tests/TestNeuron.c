#include "CuTest.h"
#include "../neuron.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

//Pour tester neuron : utiliser la commande gcc -o AllTests AllTests.c CuTest.c TestNeuron.c ../neuron.c -lm
//Pour tester les deux : utiliser la commande gcc -o AllTests AllTests.c CuTest.c TestNeuron.c TestPopulation.c ../neuron.c ../population.c -lm

//Pour tester : utiliser la commande gcc -o AllTests AllTests.c CuTest.c TestNeuron.c ../neuron.c -lm
//Puis exécuter le fichier AllTests : ./AllTests
//Un point "." signifie que le test a réussi, un "F" signifie qu'il a échoué


void TestForward(CuTest *tc) {
    Neuron neuron;
    double weights[] = {0.5, -0.3};
    neuron.weights = weights;
    neuron.output = 0;
    Neuron inputs[2] = {{.output = 1.0}, {.output = 2.0}};
    forward(&neuron, inputs, 2);
    double expected = tanh(0.5 * 1.0 + (-0.3) * 2.0);
    double actual = neuron.output;
    printf("TestForward: expected=%.6f, actual=%.6f\n", expected, actual);
    CuAssertDblEquals(tc, expected, actual, 0.001);
}

void TestInitCouche(CuTest *tc) {
    int nb_neurones = 3;
    Couche *suivante = NULL;
    Couche *couche = init_couche(nb_neurones, suivante, 1, 0);
    printf("TestInitCouche: couche=%p \n", (void*)couche);

    // Vérification de l'allocation
    CuAssertPtrNotNull(tc, couche);
    CuAssertIntEquals(tc, nb_neurones, couche->nb_neurones);
    CuAssertPtrEquals(tc, suivante, couche->p);
    CuAssertIntEquals(tc, 1, couche->is_fst_couche);
    CuAssertIntEquals(tc, 0, couche->is_lst_couche);

    // Vérification des neurones et des poids
    CuAssertPtrNotNull(tc, couche->tab_n);
    for (int i = 0; i < nb_neurones; i++) {
        for (int j = 0; j < INPUT_SIZE; j++) {
            CuAssertTrue(tc, couche->tab_n[i].weights[j] != 0.0);
        }
    }
    free(couche->tab_n);
    free(couche);
}

void TestCalculCouche(CuTest *tc) {
    Couche *couche = init_couche(3, NULL, 1, 0);
    double tab_val[2] = {1.0, 2.0};
    double *tab_result = calcul_couche(couche, tab_val, 2);
    CuAssertPtrNotNull(tc, tab_result);
    for (int i = 0; i < couche->nb_neurones; i++) {
        CuAssertTrue(tc, tab_result[i] == forward(&couche->tab_n[i], tab_val));
    }
    free(tab_result);
    free(couche->tab_n);
    free(couche);
}

void TestCalculReseau(CuTest *tc) {
    Couche *couche1 = init_couche(3, NULL, 1, 0);
    Couche *couche2 = init_couche(2, NULL, 0, 1);
    couche1->p = couche2;
    double tab_val[2] = {1.0, 2.0};
    double *tab_result = calcul_reseau(tab_val, couche1);
    CuAssertPtrNotNull(tc, tab_result);
    for (int i = 0; i < 2; i++){
        CuAssertTrue(tc, tab_result[i] == calcul_couche(couche2, calcul_couche(couche1, tab_val, 2), 3)[i]);
    }
    free(tab_result);
    free(couche1->tab_n);
    free(couche2->tab_n);
    free(couche1);
    free(couche2);
}

void TestInitReseau(CuTest *tc) {
    int nb_couches = 3;
    int taille_max = 5;
    int taille_min = 3;
    int nb_entrees = 4;
    int nb_sorties = 2;

    Couche *reseau = init_reseau(nb_couches, taille_max, taille_min, nb_entrees, nb_sorties);

    // Test premiere couche
    CuAssertIntEquals(tc, nb_entrees, reseau->nb_neurones);
    CuAssertTrue(tc, reseau->is_fst_couche);
    CuAssertTrue(tc, !reseau->is_lst_couche);

    // Test couches cachées
    Couche *hidden_layer = reseau;
    for (int i = 0; i < nb_couches - 2; i++){
        hidden_layer = hidden_layer->p;
        CuAssertTrue(tc, hidden_layer != NULL);
        CuAssertTrue(tc, !hidden_layer->is_fst_couche);
        CuAssertTrue(tc, !hidden_layer->is_lst_couche);
    }

    // Test derniere couche
    Couche *last_layer = hidden_layer->p;
    CuAssertIntEquals(tc, nb_sorties, last_layer->nb_neurones);
    CuAssertTrue(tc, !last_layer->is_fst_couche);
    CuAssertTrue(tc, last_layer->is_lst_couche);

    // Free memory
    free(reseau->tab_n);
    free(hidden_layer->tab_n);
    free(last_layer->tab_n);
    free(reseau);
    free(hidden_layer);
    free(last_layer);
}

// Ajout des tests pour fichier AllTests.c
CuSuite* NeuronGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestForward);
    SUITE_ADD_TEST(suite, TestInitCouche);
    SUITE_ADD_TEST(suite, TestCalculCouche);
    SUITE_ADD_TEST(suite, TestCalculReseau);
    SUITE_ADD_TEST(suite, TestInitReseau);
    return suite;
}
