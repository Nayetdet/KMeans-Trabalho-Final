#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#define HISTOGRAM_SIZE 256

void computeHistogram(const unsigned char *const data, unsigned char histogram[HISTOGRAM_SIZE], unsigned long long size);

#endif
