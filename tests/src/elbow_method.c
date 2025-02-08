#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pgm.h"
#include "kmeans.h"
#include "sse.h"
#include "elbow_method.h"

void executeElbowMethod(const char *srcPath, unsigned maxK, unsigned long long *sseResults) {
    PGM *srcPgm = readPGM(srcPath);
    if (!srcPgm) {
        fprintf(stderr, "Erro ao carregar a imagem %s\n", srcPath);
        return;
    }

    KMeansData kd = {
        .size = srcPgm->width * srcPgm->height,
        .maxValue = srcPgm->maxValue,
        .data = srcPgm->data
    };

    for (unsigned k = 1; k <= maxK; k++) {
        KMeans *km = getKMeans(&kd, k, MAX_ITERATIONS);
        if (!km) {
            fprintf(stderr, "Erro ao calcular KMeans para k = %u\n", k);
            freePGM(srcPgm);
            return;
        }

        sseResults[k - 1] = calculateSSE(km->clusters, kd.data, km->centroids, kd.size);

        freeKMeans(km);
    }

    freePGM(srcPgm);
}

bool writeElbowMethod (const char *srcPath, unsigned long long *sseResults, unsigned maxK) {
    char elbowResultsPath[FILENAME_MAX];
    snprintf(elbowResultsPath, sizeof(elbowResultsPath), "%s_sse.txt", srcPath);

    FILE *sseFile = fopen(elbowResultsPath, "w");
    if (!sseFile) {
        fprintf(stderr, "Erro ao criar arquivo de resultados SSE\n");
        exit(1);
    }

    for (unsigned k = 1; k <= maxK; k++) {
        fprintf(sseFile, "%u %llu\n", k, sseResults[k - 1]);
    }

    fclose(sseFile);
    return true;
}

