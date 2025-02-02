#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "kmeans.h"

KMeans *getKMeans(KMeansData *kd, unsigned char k, unsigned maxIterations) {
    if (!k || !maxIterations || !kd || !kd->data || kd->size == 0) {
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

    srand(time(NULL));
    for (unsigned char i = 0; i < km->k; i++) {
        km->centroids[i] = kd->data[rand() % kd->size];
    }

    bool hasConverged;
    unsigned numIterations = 0;

    do {
        for (unsigned long long i = 0; i < kd->size; i++) {
            unsigned char cluster;
            int minDistance = kd->maxValue;

            for (unsigned char j = 0; j < km->k; j++) {
            int distance = abs((int)(km->centroids[j] - kd->data[i]));
                if (distance < minDistance) {
                    cluster = j;
                    minDistance = distance;
                }
            }

            km->clusters[i] = cluster;
        }

        hasConverged = true;
        for (unsigned char i = 0; i < km->k; i++) {
            unsigned long long sum = 0;
            unsigned long long count = 0;

            for (unsigned long long j = 0; j < kd->size; j++) {
                if (km->clusters[j] == i) {
                    sum += kd->data[j];
                    count++;
                }
            }

            unsigned char centroid = count ? (unsigned char)(sum / count) : 0;
            if (km->centroids[i] != centroid) {
                hasConverged = false;
                km->centroids[i] = centroid;
            }
        }

        numIterations++;
    } while (!hasConverged && numIterations < km->maxIterations);

    for (unsigned long long i = 0; i < kd->size; i++) {
        kd->data[i] = km->centroids[km->clusters[i]];
    }

    return km;
}

void freeKMeans(KMeans *km) {
    if (!km) {
        return;
    }

    free(km->centroids);
    free(km->clusters);
    free(km);
}
