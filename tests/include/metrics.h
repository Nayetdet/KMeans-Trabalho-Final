#ifndef METRICS_H
#define METRICS_H

#define CELL_NUCLEUS_COLOR 29

double getDiceByBinarizingData(unsigned char *outData, unsigned char *targetData, unsigned size);
unsigned long long getSSE(const unsigned char *const data, unsigned char *const clusters, const unsigned char *const centroids, unsigned size);

#endif