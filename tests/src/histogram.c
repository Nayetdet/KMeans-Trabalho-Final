#include <stdio.h>
#include <stdbool.h>

#include "histogram.h"

void computeHistogram(const unsigned char *const data, unsigned char histogram[HISTOGRAM_SIZE], unsigned long long size) {
    for (unsigned i = 0; i < HISTOGRAM_SIZE; i++) {
        histogram[i] = 0;
    }
    
    for (unsigned long long i = 0; i < size; i++) {
        histogram[data[i]]++;
    }
}

bool saveHistogram(const char *const outPath, unsigned char histogram[HISTOGRAM_SIZE]) {
    FILE *file = fopen(outPath, "w");
    if (!file) {
        fprintf(stderr, "Erro: Falha ao abrir o arquivo para escrita\n");
        return false;
    }

    for (unsigned i = 0; i < HISTOGRAM_SIZE; i++) {
        fprintf(file, "%u ", histogram[i]);      
    }
    
    printf("Histograma salvo em: %s\n", outPath);
    fclose(file);
    return true;
}
