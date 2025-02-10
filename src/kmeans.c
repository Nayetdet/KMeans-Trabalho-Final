// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
// * Aluno: João Pedro Moreira Campos de Lima              *
// * Matrícula: 20241045050391                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
// * Aluno: Isaac da Cunha Cavalcanti Duarte               *
// * Matrícula: 20241045050375                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
// * Aluno: Josué Rodrigues Avelino                        *
// * Matrícula: 20241045050219                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
// * Aluno: Orleoncio Maciel                               *
// * Matrícula: 20181045050165                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "kmeans.h"

static void initCentroids(KMeans *km, const KMeansData *const kd);
static void assignClusters(KMeans *km, const KMeansData *const kd);
static bool updateCentroids(KMeans *km, const KMeansData *const kd);

KMeans *getKMeans(const KMeansData *const kd, unsigned char k, unsigned maxIterations) {
    if (!k || !maxIterations || !kd || !kd->data || !kd->size) {
        return NULL;
    }

    KMeans *km = (KMeans *)malloc(sizeof(KMeans));
    if (!km) {
        return NULL;
    }

    km->k = k;
    km->maxIterations = maxIterations;
    km->centroids = (unsigned char *)malloc(km->k * sizeof(unsigned char));
    km->clusters = (unsigned char *)malloc(kd->size * sizeof(unsigned char));
    if (!km->centroids || !km->clusters) {
        freeKMeans(km);
        return NULL;
    }

    initCentroids(km, kd);
    for (unsigned numIterations = 0; numIterations < km->maxIterations; numIterations++) {
        assignClusters(km, kd);
        if (!updateCentroids(km, kd)) {
            break;
        }
    }

    return km;
}

bool applyKMeans(KMeansData *kd, unsigned char k, unsigned maxIterations) {
    KMeans *km = getKMeans(kd, k, maxIterations);
    if (!km) {
        return false;
    }

    for (unsigned i = 0; i < kd->size; i++) {
        kd->data[i] = km->centroids[km->clusters[i]];
    }

    freeKMeans(km);
    return true;
}

void freeKMeans(KMeans *km) {
    if (!km) {
        return;
    }

    if (km->centroids) {
        free(km->centroids);
        km->centroids = NULL;
    }

    if (km->clusters) {
        free(km->clusters);
        km->clusters = NULL;
    }

    free(km);
}

static void initCentroids(KMeans *km, const KMeansData *const kd) {
    for (unsigned k = 0; k < km->k; k++) {
        unsigned idx = rand() % kd->size;
        km->centroids[k] = kd->data[idx];
    }
}

static void assignClusters(KMeans *km, const KMeansData *const kd) {
    for (unsigned i = 0; i < kd->size; i++) {
        unsigned char cluster = 0;
        int minDistance = kd->maxValue;

        for (unsigned k = 0; k < km->k; k++) {
            int distance = abs((int)km->centroids[k] - (int)kd->data[i]);
            if (distance < minDistance) {
                cluster = k;
                minDistance = distance;
            }
        }

        km->clusters[i] = cluster;
    }
}

static bool updateCentroids(KMeans *km, const KMeansData *const kd) {
    bool hasUpdated = false;
    for (unsigned k = 0; k < km->k; k++) {
        unsigned long long sum = 0;
        unsigned long long count = 0;
        
        for (unsigned i = 0; i < kd->size; i++) {
            if (km->clusters[i] == k) {
                sum += kd->data[i];
                count++;
            }
        }

        unsigned char centroid = (count) ? (unsigned char)(sum / count) : 0;
        if (km->centroids[k] != centroid) {
            km->centroids[k] = centroid;
            hasUpdated = true;
        }
    }

    return hasUpdated;
}
