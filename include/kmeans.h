#ifndef KMEANS_H
#define KMEANS_H

#include <stdbool.h>

#include "pgm.h"

typedef struct {
    unsigned int k;
    unsigned char *centroids;
    unsigned char **clusters;
} KMeans;

bool applyKMeans(PGM *pgm, unsigned int k);

#endif
