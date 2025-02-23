#include "CuTest.h"
#include "../neuron.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Pour tester : utiliser la commande gcc -o AllTests AllTests.c CuTest.c TestNeuron.c neuron.c -lm
//Puis exécuter le fichier AllTests : ./AllTests
//Un point "." signifie que le test a réussi, un "F" signifie qu'il a échoué


void TestTransfer(CuTest *tc) {
    double input = 1.5;
    double expected = tanh(input);
    double actual = transfer(input);
    printf("TestTransfer: expected=%.6f, actual=%.6f\n", expected, actual);
    CuAssertDblEquals(tc, expected, actual, 0.001);
}

void TestForward(CuTest *tc) {
    Neuron neuron = {{0.5, -0.3}};
    double inputs[INPUT_SIZE] = {1.0, 2.0};
    double expected = transfer(0.5 * 1.0 + (-0.3) * 2.0); // résultat = 0.5 - 0.6 = -0.1
    double actual = forward(&neuron, inputs);
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



// Ajout des tests pour fichier AllTests.c
CuSuite* NeuronGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestTransfer);
    SUITE_ADD_TEST(suite, TestForward);
    SUITE_ADD_TEST(suite, TestInitCouche);
    return suite;
}