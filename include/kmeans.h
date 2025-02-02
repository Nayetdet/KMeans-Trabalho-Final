#ifndef KMEANS_H
#define KMEANS_H

typedef struct {
    unsigned long long size;
    unsigned char maxValue;
    unsigned char *data;
} KMeansData;

typedef struct {
    unsigned char k;
    unsigned maxIterations;
    unsigned char *centroids;
    unsigned char *clusters;
} KMeans;

KMeans *getKMeans(KMeansData *kd, unsigned char k, unsigned maxIterations);
void freeKMeans(KMeans *km);

#endif
