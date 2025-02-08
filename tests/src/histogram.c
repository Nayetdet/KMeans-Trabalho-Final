#include <stdio.h>
#include <stdbool.h>

#include "histogram.h"

void computeHistogram(unsigned char histogram[UCHAR_MAX], const unsigned char *const data, unsigned size) {
    for (unsigned i = 0; i < UCHAR_MAX; i++) {
        histogram[i] = 0;
    }
    
    for (unsigned i = 0; i < size; i++) {
        histogram[data[i]]++;
    }
}

bool writeHistogram(unsigned char histogram[UCHAR_MAX], const char *const outPath) {
    FILE *file = fopen(outPath, "w");
    if (!file) {
        fprintf(stderr, "Erro: Falha ao abrir o arquivo para escrita\n");
        return false;
    }

    for (unsigned i = 0; i < UCHAR_MAX; i++) {
        fprintf(file, "%u ", histogram[i]);      
    }
    
    printf("Histograma salvo em: %s\n", outPath);
    fclose(file);
    return true;
}
