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
    CuAssertIntEquals(tc, 0, getR(c));
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
    CuAssertIntEquals(tc, 2, getG(c));
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
    CuAssertIntEquals(tc, 255, getR(getColor(p)));
    CuAssertIntEquals(tc, 255, getG(getColor(p)));
    CuAssertIntEquals(tc, 255, getB(getColor(p)));
    CuAssertIntEquals(tc, 255, getA(getColor(p)));
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

void TestGetDatasetSize(CuTest *tc){
    Dataset d = createDataset();
    d->size = 30;
    CuAssertIntEquals(tc, 30, getDatasetSize(d));
    destroyDataset(d);
}

void TestCreateDataset(CuTest *tc){
    Dataset d = createDataset();
    CuAssertPtrEquals(tc, NULL, d->tab);
    CuAssertIntEquals(tc, 0, getDatasetSize(d));
    destroyDataset(d);
}

void TestAddDatasetPixel(CuTest * tc){
    Dataset d = createDataset();
    Color c = createColor(0, 0, 0, 0);
    Pixel p = createPixel(0., 0., c);
    CuAssertIntEquals(tc, 0, getDatasetSize(d));
    addDatasetPixel(d, p);
    CuAssertIntEquals(tc, 1, getDatasetSize(d));
    CuAssertIntEquals(tc, 0, getR(getColor(getDatasetPixel(d, 0))));
    CuAssertIntEquals(tc, 0, getG(getColor(getDatasetPixel(d, 0))));
    CuAssertIntEquals(tc, 0, getB(getColor(getDatasetPixel(d, 0))));
    CuAssertIntEquals(tc, 0, getA(getColor(getDatasetPixel(d, 0))));
    CuAssertIntEquals(tc, 0., getX(getDatasetPixel(d, 0)));
    CuAssertIntEquals(tc, 0., getY(getDatasetPixel(d, 0)));
    destroyDataset(d);
    destroyColor(c);
    destroyPixel(p);
}

void TestGetDatasetPixel(CuTest *tc){
    Dataset d = createDataset();
    Color c = createColor(0, 0, 0, 0);
    Pixel p1 = createPixel(0., 0., c);
    Pixel p2 = createPixel(1., 0., c);
    Pixel p3 = createPixel(2., 0., c);
    addDatasetPixel(d, p1);
    addDatasetPixel(d, p2);
    addDatasetPixel(d, p3);
    CuAssertDblEquals(tc, 0., getX(getDatasetPixel(d, 0)), 0.);
    CuAssertDblEquals(tc, 1., getX(getDatasetPixel(d, 1)), 0.);
    CuAssertDblEquals(tc, 2., getX(getDatasetPixel(d, 2)), 0.);
    destroyDataset(d);
    destroyColor(c);
    destroyPixel(p1);
    destroyPixel(p2);
    destroyPixel(p3);
}

void TestCreatePopulation(CuTest *tc) {
    Color c = createColor(255, 0, 0, 255);
    Dataset d = createDataset();
    double val = 1.;
    int size = 2;
    createPopulation(d, c, val, size);
    CuAssertIntEquals(tc, size, getDatasetSize(d)); // Vérification de l'effet de la création
    CuAssertDblEquals(tc, val * (0.2 * cos(0.2)), getX(getDatasetPixel(d, 1)), 0.); // Vérification de l'effet de la création
    CuAssertDblEquals(tc, val * (0.2 * sin(0.2)), getY(getDatasetPixel(d, 1)), 0.); // Vérification de l'effet de la création
    destroyColor(c);
    destroyDataset(d);
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
    SUITE_ADD_TEST(suite, TestGetDatasetSize);
    SUITE_ADD_TEST(suite, TestCreateDataset);
    SUITE_ADD_TEST(suite, TestAddDatasetPixel);
    SUITE_ADD_TEST(suite, TestGetDatasetPixel);
    return suite;
}