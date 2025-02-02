#ifndef KMEANS_H
#define KMEANS_H

#include <stdbool.h>

typedef struct {
    unsigned width;
    unsigned height;
    unsigned char maxValue;
    unsigned char **data;
} KMeansData;

typedef struct {
    unsigned k;
    unsigned maxIterations;
    unsigned char *centroids;
    unsigned char **clusters;
    unsigned *clusterSizes;
} KMeans;

bool applyKMeans(KMeansData *kd, unsigned k, unsigned maxIterations);

#endif
