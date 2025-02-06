#include <stdio.h>

#include "metrics.h"
#include "histogram.h"

void computeHistogram(const unsigned char *const data, unsigned char histogram[HISTOGRAM_SIZE], unsigned long long size) {
    for (unsigned long long i = 0; i < size; i++) {
        histogram[data[i]]++;
    }
}