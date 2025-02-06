#include <stdio.h>

#include "metrics.h"
#include "histogram.h"

void computeHistogram(const unsigned char *const data, unsigned char histogram[HISTOGRAM_SIZE], unsigned long long size) {
    for (unsigned long long i = 0; i < size; i++) {
        histogram[data[i]]++;
    }
}

void salvarHistograma(const char *filename, unsigned char histogram[HISTOGRAM_SIZE]){

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", OUTPUT_PATH, filename);


    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("ERRO: Erro ao abrir o arquivo para escrita");
        return;
    }

    fprintf(file, "[ ");
    for (unsigned i = 0; i < HISTOGRAM_SIZE; i++)
    {
        fprintf(file, " %u, ", histogram[i]);      
    }
    fprintf(file, " ]");
    

    fclose(file);
    printf("Histograma salvo em: %s\n", filepath);
}
