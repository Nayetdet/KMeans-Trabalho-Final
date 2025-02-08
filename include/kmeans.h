#ifndef KMEANS_H
#define KMEANS_H

#include <stdbool.h>

typedef struct {
    unsigned size;
    unsigned char maxValue;
    unsigned char *data;
} KMeansData;

typedef struct {
    unsigned char k;
    unsigned maxIterations;
    unsigned char *centroids;
    unsigned char *clusters;
} KMeans;

KMeans *getKMeans(const KMeansData *const kd, unsigned char k, unsigned maxIterations);
bool applyKMeans(KMeansData *kd, unsigned char k, unsigned maxIterations);
void freeKMeans(KMeans *km);

#endif
