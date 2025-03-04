#include "CuTest.h"
#include "../population.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

//Pour tester population : utiliser la commande gcc -o AllTests AllTests.c TestPopulation.c ../population.c CuTest.c -lm -lSDL2
//Pour tester les deux : utiliser la commande gcc -o AllTests AllTests.c CuTest.c TestNeuron.c TestPopulation.c ../neuron.c ../population.c -lm -lSDL2

//Puis exécuter le fichier AllTests : ./AllTests
//Un point "." signifie que le test a réussi, un "F" signifie qu'il a échoué

void TestGetR(CuTest *tc) {
    int r = 255;
    int g = 100;
    int b = 50;
    int a = 200;
    Color c = createColor(r, g, b, a);
    int res = getR(c);
    CuAssertIntEquals(tc, r, res);
}

void TestGetG(CuTest *tc) {
    int r = 255;
    int g = 100;
    int b = 50;
    int a = 200;
    Color c = createColor(r, g, b, a);
    int res = getG(c);
    CuAssertIntEquals(tc, g, res);
}

void TestGetB(CuTest *tc) {
    int r = 255;
    int g = 100;
    int b = 50;
    int a = 200;
    Color c = createColor(r, g, b, a);
    int res = getB(c);
    CuAssertIntEquals(tc, b, res);
}

void TestGetA(CuTest *tc) {
    int r = 255;
    int g = 100;
    int b = 50;
    int a = 200;
    Color c = createColor(r, g, b, a);
    int res = getA(c);
    CuAssertIntEquals(tc, a, res);
}

void TestSetR(CuTest *tc) {
    int r = 255;
    int r2 = 3;
    int r3 = 256;
    int g = 100;
    int b = 50;
    int a = 200;
    Color c = createColor(r, g, b, a);
    setR(c, r2);
    CuAssertIntEquals(tc, r2, getR(c));
    setR(c, r3);
    CuAssertIntEquals(tc, 1, getR(c));
}

void TestSetG(CuTest *tc) {
    int r = 255;
    int g = 100;
    int g2 = 15;
    int g3 = -254;
    int b = 50;
    int a = 200;
    Color c = createColor(r, g, b, a);
    setG(c, g2);
    CuAssertIntEquals(tc, g2, getG(c));
    setG(c, g3);
    CuAssertIntEquals(tc, 1, getG(c));
}

void TestSetB(CuTest *tc) {
    int r = 255;
    int g = 100;
    int b = 50;
    int b2 = 18;
    int a = 200;
    Color c = createColor(r, g, b, a);
    setB(c, b2);
    CuAssertIntEquals(tc, b2, getB(c));
}

void TestSetA(CuTest *tc) {
    int r = 255;
    int g = 100;
    int b = 50;
    int a = 200;
    int a2 = 183;
    Color c = createColor(r, g, b, a);
    setA(c, a2);
    CuAssertIntEquals(tc, a2, getA(c));
}

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

void TestCreatePixelTab (CuTest *tc) {
    Color c = createColor(0, 0, 255, 255);
    int width = 100;
    int height = 50;
    Pixel** tabPix = createPixelTab(width, height, c);

    //Tests allocations
    CuAssertPtrNotNull(tc, tabPix);
    for (int i = 0; i < width; i++) {
        CuAssertPtrNotNull(tc, tabPix[i]);
    }
    
    destroyPixelTab(tabPix, width, height);
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
    createPopulation(img, c, 1);
    CuAssertPtrEquals(tc, c, getPixelColor(img, 50, 50)); // Vérification de l'effet de la création
    destroyImage(img);
    destroyColor(c);
}

CuSuite* PopulationGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestGetR);
    SUITE_ADD_TEST(suite, TestGetG);
    SUITE_ADD_TEST(suite, TestGetB);
    SUITE_ADD_TEST(suite, TestGetA);
    SUITE_ADD_TEST(suite, TestSetR);
    SUITE_ADD_TEST(suite, TestSetG);
    SUITE_ADD_TEST(suite, TestSetB);
    SUITE_ADD_TEST(suite, TestSetA);
    SUITE_ADD_TEST(suite, TestCreateColor);
    SUITE_ADD_TEST(suite, TestCreatePixel);
    SUITE_ADD_TEST(suite, TestCreatePixelTab);
    SUITE_ADD_TEST(suite, TestCreateImage);
    SUITE_ADD_TEST(suite, TestCreatePopulation);
    return suite;
}