#include "CuTest.h"
#include "../population.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Pour tester population : utiliser la commande gcc -o AllTests AllTests.c TestPopulation.c ../population.c CuTest.c -lm
//Pour tester les deux : utiliser la commande gcc -o AllTests AllTests.c CuTest.c TestNeuron.c TestPopulation.c ../neuron.c ../population.c -lm

//Puis exécuter le fichier AllTests : ./AllTests
//Un point "." signifie que le test a réussi, un "F" signifie qu'il a échoué

void TestCreateColor(CuTest *tc) {
    Color c = createColor(255, 100, 50, 200); // crée une nouvelle couleur
    CuAssertIntEquals(tc, 255, getR(c)); //verif si composante R (RVB) de c = 255 
    // tc = obj test, 255 = valeur attendue, getR(c) = valeur retournée 
    CuAssertIntEquals(tc, 100, getG(c));
    CuAssertIntEquals(tc, 50, getB(c));
    CuAssertIntEquals(tc, 200, getA(c));
    destroyColor(c);
}

void TestCreatePixel(CuTest *tc) {
    Color c = createColor(255, 255, 255, 255);
    Pixel p = createPixel(10, 20, c);
    CuAssertIntEquals(tc, 10, getX(p));
    CuAssertIntEquals(tc, 20, getY(p));
    CuAssertPtrEquals(tc, c, getColor(p));
    destroyPixel(p);
    destroyColor(c);
}

void TestCreateImage(CuTest *tc) {
    Color c = createColor(0, 0, 255, 255);
    Image img = createImage(100, 50, c);
    CuAssertIntEquals(tc, 100, getWidth(img));
    CuAssertIntEquals(tc, 50, getHeight(img));
    CuAssertPtrNotNull(tc, getPixel(img, 10, 10));
    destroyImage(img);
    destroyColor(c);
}

void TestCreatePopulation(CuTest *tc) {
    Color c = createColor(255, 0, 0, 255);
    Image img = createImage(100, 100, c);
    createPopulation(img, 10, c, true);
    CuAssertPtrEquals(tc, c, getPixelColor(img, 50, 50)); // Vérification de l'effet de la création
    destroyImage(img);
    destroyColor(c);
}

CuSuite* PopulationGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestCreateColor);
    SUITE_ADD_TEST(suite, TestCreatePixel);
    SUITE_ADD_TEST(suite, TestCreateImage);
    SUITE_ADD_TEST(suite, TestCreatePopulation);
    return suite;
}