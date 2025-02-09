#ifndef SSE_H
#define SSE_H

#include <stdbool.h>

unsigned long long getSSE(const unsigned char *const data, unsigned char *const clusters, const unsigned char *const centroids, unsigned size);
unsigned long long *getSSEs(const char *const initialPath, unsigned char maxK, unsigned maxIterations);
bool writeSSEs(const unsigned long long *const sses, const char *const elbowPath, unsigned char maxK);

#endif
