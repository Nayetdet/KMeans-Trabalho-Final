#include "sse.h"

double calculateSSE(unsigned long long size, const unsigned char *const data, unsigned char *const clusters, const unsigned char *const centroids) {
    unsigned long long sse = 0;
    for (unsigned long long i = 0; i < size; i++) {
        int error = (int)data[i] - (int)centroids[clusters[i]];
        sse += error * error;
    }
    
    return sse;
}
