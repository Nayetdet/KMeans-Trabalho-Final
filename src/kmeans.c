#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "kmeans.h"

#define CLUSTER_INITIAL_SIZE 100
#define CLUSTER_SIZE_INCREMENT 50

static bool assignClusters(KMeans *km, const KMeansData *const kd);
static unsigned char calculateCentroid(const KMeans *const km, const KMeansData *const kd, unsigned centroidIdx);
static unsigned getClosestCentroidIndex(const KMeans *const km, unsigned char data);
static void freeKMeans(KMeans *km);

bool applyKMeans(KMeansData *kd, unsigned k, unsigned maxIterations) {
    KMeans *km = (KMeans *)malloc(sizeof(KMeans));
    if (!km) {
        return false;
    }

    km->k = k;
    km->maxIterations = maxIterations;
    if (!km->k || !km->maxIterations) {
        return false;
    }

    km->centroids = (unsigned char *)malloc(km->k * sizeof(unsigned char));
    km->clusters = (unsigned char **)malloc(km->k * sizeof(unsigned char **));
    km->clusterSizes = (unsigned *)malloc(km->k * sizeof(unsigned));
    if (!km->centroids || !km->clusters || !km->clusterSizes) {
        freeKMeans(km);
        return false;
    }

    for (unsigned i = 0; i < km->k; i++) {
        km->clusters[i] = (unsigned char *)malloc(CLUSTER_INITIAL_SIZE * sizeof(unsigned char));
        if (!km->clusters[i]) {
            freeKMeans(km);
            return false;
        }

        km->centroids[i] = rand() % kd->maxValue; 
    }

    if (!assignClusters(km, kd)) {
        freeKMeans(km);
        return false;
    }

    for (unsigned i = 0; i < kd->height; i++) {
        for (unsigned j = 0; j < kd->width; j++) {
            unsigned clusterIdx = getClosestCentroidIndex(km, kd->data[i][j]);
            kd->data[i][j] = km->centroids[clusterIdx];
        }
    }

    freeKMeans(km);
    return true;
}

static bool assignClusters(KMeans *km, const KMeansData *const kd) {
    bool hasConverged;
    unsigned numIterations = 0;

    do {
        for (unsigned i = 0; i < km->k; i++) {
            km->clusterSizes[i] = 0;
        }

        for (unsigned i = 0; i < kd->height; i++) {
            for (unsigned j = 0; j < kd->width; j++) {
                unsigned char data = kd->data[i][j];
                unsigned clusterIdx = getClosestCentroidIndex(km, data);
                unsigned dataIdx = km->clusterSizes[clusterIdx];

                if (dataIdx > 0 && !(dataIdx % CLUSTER_SIZE_INCREMENT)) {
                    unsigned long long newSize = (dataIdx + CLUSTER_SIZE_INCREMENT) * sizeof(unsigned char);
                    unsigned char *newCluster = (unsigned char *)realloc(km->clusters[clusterIdx], newSize);
                    if (!newCluster) {
                        return false;
                    }

                    km->clusters[clusterIdx] = newCluster;
                }

                km->clusters[clusterIdx][dataIdx] = data;
                km->clusterSizes[clusterIdx]++;
            }
        }

        hasConverged = true;
        for (unsigned i = 0; i < km->k; i++) {
            unsigned char centroid = calculateCentroid(km, kd, i);
            if (km->centroids[i] != centroid) {
                hasConverged = false;
            }
            
            km->centroids[i] = centroid;
        }

        numIterations++;
    } while (!hasConverged || numIterations < km->maxIterations);
    return true;
}

static unsigned getClosestCentroidIndex(const KMeans *const km, unsigned char data) {
    unsigned minIdx = 0;
    int minDistance = 255;

    for (unsigned i = 0; i < km->k; i++) {
        int distance = abs(km->centroids[i] - data);
        if (distance < minDistance) {
            minIdx = i;
            minDistance = distance;
        }
    }

    return minIdx;
}

static unsigned char calculateCentroid(const KMeans *const km, const KMeansData *const kd, unsigned centroidIdx) {
    unsigned long long sum = 0;
    unsigned long long count = 0;
    
    for (unsigned i = 0; i < kd->height; i++) {
        for (unsigned j = 0; j < kd->width; j++) {
            unsigned char data = kd->data[i][j];
            if (getClosestCentroidIndex(km, data) == centroidIdx) {
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
        for (unsigned i = 0; i < km->k; i++) {
            free(km->clusters[i]);
        }

        free(km->clusters);
    }
    
    free(km->centroids);
    free(km->clusterSizes);
    free(km);
}
