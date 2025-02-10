#ifndef UTILS_H
#define UTILS_H

void binarizeData(unsigned char *data, unsigned size, unsigned char value);
unsigned char getLowestValue(const unsigned char *const data, unsigned size);
double getMean(const double *const data, unsigned size);
double getStandardDeviation(const double *const data, double mean, unsigned size);

#endif
