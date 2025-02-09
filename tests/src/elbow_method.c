#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "pgm.h"
#include "kmeans.h"
#include "metrics.h"
#include "elbow_method.h"

void calculateElbowMethod(unsigned long long *sses, const char *const initialPgmFilePath, unsigned char kMax) {
    PGM *initialPgm = readPGM(initialPgmFilePath);
    if (!initialPgm) {
        fprintf(stderr, "Erro: Falha ao ler a imagem de entrada\n");
        return;
    }

    KMeansData kd = {
        .size = initialPgm->width * initialPgm->height,
        .maxValue = initialPgm->maxValue,
        .data = initialPgm->data
    };

    for (unsigned char k = 1; k <= kMax; k++) {
        KMeans *km = getKMeans(&kd, k, UCHAR_MAX);
        if (!km) {
            fprintf(stderr, "Erro: Falha ao aplicar o algoritmo k-means na imagem com k = %hhu\n", k);
            freePGM(initialPgm);
            return;
        }

        sses[k - 1] = getSSE(kd.data, km->clusters, km->centroids, kd.size);
    }

    freePGM(initialPgm);
}

bool writeElbowMethod(const unsigned long long *const sses, const char *const elbowPath, unsigned char kMax) {
    FILE *fp = fopen(elbowPath, "w");
    if (!fp) {
        fprintf(stderr, "Erro: Falha ao abrir o arquivo para escrita\n");
        exit(1);
    }

    for (unsigned char k = 1; k <= kMax; k++) {
        fprintf(fp, "%u %llu\n", k, sses[k - 1]);
    }

    fclose(fp);
    return true;
}
