#include "CuTest.h"
#include <stdio.h>

CuSuite* NeuronGetSuite();

void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuiteAddSuite(suite, NeuronGetSuite());  // Ajout des tests

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("\nRésultats des tests :\n");
    printf("%s\n", output->buffer);
}

int main(void) {
    RunAllTests();
}