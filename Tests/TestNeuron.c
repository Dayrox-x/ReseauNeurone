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
    Couche *couche = init_couche(nb_neurones, suivante, NULL, true, false);
    printf("TestInitCouche: couche=%p \n", (void*)couche);

    // Vérification de l'allocation
    CuAssertPtrNotNull(tc, couche);
    CuAssertIntEquals(tc, nb_neurones, couche->nb_neurones);
    CuAssertPtrEquals(tc, suivante, couche->next);
    CuAssertTrue(tc, couche->is_fst_couche);
    CuAssertIntEquals(tc, 0, couche->is_lst_couche);

    free(couche->tab_n);
    free(couche);
}

void TestCalculCouche(CuTest *tc) {
    int nb_neuron = 2;
    Couche *couche1 = init_couche(nb_neuron, NULL, NULL, false, true);
    Couche *couche0 = init_couche(nb_neuron, couche1, NULL, true, false);
    Couche *coucheB = init_couche(nb_neuron, NULL, NULL, false, true);
    Couche *coucheA = init_couche(nb_neuron, coucheB, NULL, true, false);
    couche1->prev = couche0;
    coucheB->prev = coucheA;
    init_neuron(couche0, 1);
    for (int i = 0; i < 2; i++){
        coucheA->tab_n[i].weights = couche0->tab_n[i].weights;
        coucheA->tab_n[i].output = couche0->tab_n[i].output;
        coucheA->tab_n[i].delta = couche0->tab_n[i].delta;
        coucheB->tab_n[i].weights = couche1->tab_n[i].weights;
        coucheB->tab_n[i].output = couche1->tab_n[i].output;
        coucheB->tab_n[i].delta = couche1->tab_n[i].delta;
    }

    calcul_couche(couche1, couche0->tab_n);
    for (int i = 0; i < couche1->nb_neurones; i++) {
        forward(&coucheB->tab_n[i], coucheA->tab_n, coucheA->nb_neurones);
        CuAssertTrue(tc, coucheB->tab_n[i].output == couche1->tab_n[i].output);
    }
    free(couche0->tab_n);
    free(couche0);
    free(couche1->tab_n);
    free(couche1);
    free(coucheB->tab_n);
    free(coucheB);
    free(coucheA->tab_n);
    free(coucheA);
}

void TestCalculReseau(CuTest *tc) {
    int nb_neuron = 2;
    Couche *couche1 = init_couche(nb_neuron, NULL, NULL, false, true);
    Couche *couche0 = init_couche(nb_neuron, couche1, NULL, true, false);
    Couche *coucheB = init_couche(nb_neuron, NULL, NULL, false, true);
    Couche *coucheA = init_couche(nb_neuron, coucheB, NULL, true, false);
    couche1->prev = couche0;
    coucheB->prev = coucheA;
    init_neuron(couche0, 1);
    double tab_val[nb_neuron];
    for (int i = 0; i < nb_neuron; i++){
        tab_val[i] = 1.0;
        coucheA->tab_n[i].weights = couche0->tab_n[i].weights;
        coucheA->tab_n[i].output = 1.0;
        coucheA->tab_n[i].delta = couche0->tab_n[i].delta;
        coucheB->tab_n[i].weights = couche1->tab_n[i].weights;
        coucheB->tab_n[i].output = couche1->tab_n[i].output;
        coucheB->tab_n[i].delta = couche1->tab_n[i].delta;
    }
    calcul_reseau(tab_val, couche0);
    Couche * curr = coucheA;
    for (int i = 0; i < nb_neuron; i++) {
        calcul_couche(coucheB, coucheA->tab_n);
        double outputB = coucheB->tab_n[i].output;
        double output1 = couche1->tab_n[i].output;
        CuAssertDblEquals(tc, outputB, output1, 0.);
    }

    free(couche1->tab_n);
    free(couche0->tab_n);
    free(couche1);
    free(couche0);
    free(coucheA->tab_n);
    free(coucheB->tab_n);
    free(coucheA);
    free(coucheB);
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
        hidden_layer = hidden_layer->next;
        CuAssertTrue(tc, hidden_layer != NULL);
        CuAssertTrue(tc, !hidden_layer->is_fst_couche);
        CuAssertTrue(tc, !hidden_layer->is_lst_couche);
    }

    // Test derniere couche
    Couche *last_layer = hidden_layer->next;
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
