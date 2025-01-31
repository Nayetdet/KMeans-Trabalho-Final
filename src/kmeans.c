#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "kmeans.h"
#include "pgm.h"

static void assignDataToClusters(KMeans *km, PGM *pgm);
static unsigned int getClosestCentroidIndex(const KMeans *const km, const PGM *const pgm, unsigned char data);
static unsigned char calculateCentroid(const KMeans *const km, const PGM *const pgm, unsigned int centroidIdx);
static void freeKMeans(KMeans *km);

bool applyKMeans(PGM *pgm, unsigned int k) {
    KMeans *km = (KMeans *)malloc(sizeof(KMeans));
    if (!km) {
        return false;
    }

    km->k = k;
    km->centroids = (unsigned char *)malloc(km->k * sizeof(unsigned char));
    km->clusters = (unsigned char **)malloc(km->k * sizeof(unsigned char *));
    if (!km->centroids || !km->clusters) {
        freeKMeans(km);
        return false;
    }

    for (unsigned int i = 0; i < km->k; i++) {
        km->clusters[i] = (unsigned char *)malloc(pgm->width * pgm->height * sizeof(unsigned char));
        if (!km->clusters[i]) {
            freeKMeans(km);
            return false;
        }
    }

    assignDataToClusters(km, pgm);
    freeKMeans(km);
    return true;
}

static void assignDataToClusters(KMeans *km, PGM *pgm) {
    for (unsigned int i = 0; i < km->k; i++) {
        km->centroids[i] = rand() % pgm->maxValue; 
    }

    bool converged;
    do {
        unsigned int idx = 0;
        for (unsigned int i = 0; i < pgm->height; i++) {
            for (unsigned int j = 0; j < pgm->width; j++) {
                unsigned char data = pgm->data[i][j];
                unsigned int clusterIdx = getClosestCentroidIndex(km, pgm, data);
                km->clusters[clusterIdx][idx++] = data;
            }
        }

        converged = true;
        for (unsigned int i = 0; i < km->k; i++) {
            unsigned char centroid = calculateCentroid(km, pgm, i);
            if (km->centroids[i] != centroid) {
                converged = false;
            }

            km->centroids[i] = centroid;
        }
    } while (!converged);

    for (unsigned int i = 0; i < pgm->height; i++) {
        for (unsigned int j = 0; j < pgm->width; j++) {
            unsigned int clusterIdx = getClosestCentroidIndex(km, pgm, pgm->data[i][j]);
            pgm->data[i][j] = km->centroids[clusterIdx];
        }
    }
}

static unsigned int getClosestCentroidIndex(const KMeans *const km, const PGM *const pgm, unsigned char data) {
    unsigned int minIdx = 0;
    int minDistance = pgm->maxValue;

    for (unsigned int i = 0; i < km->k; i++) {
        int distance = abs(km->centroids[i] - data);
        if (distance < minDistance) {
            minIdx = i;
            minDistance = distance;
        }
    }

    return minIdx;
}

static unsigned char calculateCentroid(const KMeans *const km, const PGM *const pgm, unsigned int centroidIdx) {
    unsigned long long sum = 0;
    unsigned long long count = 0;

    for (unsigned int i = 0; i < pgm->height; i++) {
        for (unsigned int j = 0; j < pgm->width; j++) {
            unsigned char data = pgm->data[i][j];
            if (getClosestCentroidIndex(km, pgm, data) == centroidIdx) {
                sum += data;
                count++;
            }
        }
    }

    if (!count) {
        return 0;
    }

    return (unsigned char)(sum / count);
}

static void freeKMeans(KMeans *km) {
    if (!km) {
        return;
    }

    if (km->clusters) {
        for (unsigned int i = 0; i < km->k; i++) {
            free(km->clusters[i]);
        }

        free(km->clusters);
    }

    free(km->centroids);
    free(km);
}
