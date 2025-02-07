#ifndef METRICS_H
#define METRICS_H

double calculateDice(const unsigned char *const a, const unsigned char *const b, unsigned size);
double calculateSSE(unsigned long long size, const unsigned char *const data, unsigned char *const clusters, const unsigned char *const centroids);

#endif
