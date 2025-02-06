#include "metrics.h"

double calculateDice(const unsigned char *const a, const unsigned char *const b, unsigned size) {
    unsigned intersectionCount = 0;
    for (unsigned i = 0; i < size; i++) {
        if (a[i] == b[i]) {
            intersectionCount++;
        }
    }

    return (2.0 * intersectionCount) / (size + size);
}

double calculateSSE(unsigned long long size, const unsigned char *const data, unsigned char *const clusters, const unsigned char *const centroids) {
    unsigned long long sse = 0;
    for (unsigned long long i = 0; i < size; i++) {
        int error = (int)data[i] - (int)centroids[clusters[i]];
        sse += error * error;
    }
    
    return sse;
}
