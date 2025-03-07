// *********************************************************
// * Aluno: João Pedro Moreira Campos de Lima              *
// * Matrícula: 20241045050391                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
// * Aluno: Isaac da Cunha Cavalcanti Duarte               *
// * Matrícula: 20241045050375                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
// * Aluno: Josué Rodrigues Avelino                        *
// * Matrícula: 20241045050219                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
// * Aluno: Orleoncio Maciel                               *
// * Matrícula: 20181045050165                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pgm.h"
#include "kmeans.h"
#include "sse.h"

unsigned long long getSSE(const unsigned char *const data, unsigned char *const clusters, const unsigned char *const centroids, unsigned size) {
    unsigned long long sse = 0;
    for (unsigned i = 0; i < size; i++) {
        int error = (int)data[i] - (int)centroids[clusters[i]];
        sse += error * error;
    }
    
    return sse;
}

unsigned long long *getSSEs(const char *const initialPath, unsigned char maxK, unsigned maxIterations) {
    PGM *initialPgm = readPGM(initialPath);
    unsigned long long *sses = (unsigned long long *)malloc(maxK * sizeof(unsigned long long));
    if (!initialPgm || !sses) {
        freePGM(initialPgm);
        free(sses);
        return NULL;
    }

    KMeansData kd = {
        .size = initialPgm->width * initialPgm->height,
        .maxValue = initialPgm->maxValue,
        .data = initialPgm->data
    };

    for (unsigned k = 1; k <= maxK; k++) {
        KMeans *km = getKMeans(&kd, k, maxIterations);
        if (!km) {
            freePGM(initialPgm);
            free(sses);
            return NULL;
        }

        sses[k - 1] = getSSE(kd.data, km->clusters, km->centroids, kd.size);
        freeKMeans(km);
    }

    freePGM(initialPgm);
    return sses;
}

bool writeSSEs(const unsigned long long *const sses, const char *const ssePath, unsigned char maxK) {
    FILE *fp = fopen(ssePath, "w");
    if (!fp) {
        fprintf(stderr, "Erro: Falha ao abrir o arquivo para escrita\n");
        return false;
    }

    for (unsigned k = 1; k <= maxK; k++) {
        fprintf(fp, "%u %llu\n", k, sses[k - 1]);
    }

    printf("SSE salvo em: %s\n", ssePath);
    fclose(fp);
    return true;
}
