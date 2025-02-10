#ifndef UTILS_H
#define UTILS_H

void binarizeData(unsigned char *data, unsigned size, unsigned char value);
unsigned char getLowestDataValue(const unsigned char *const data, unsigned size);
double getDataMean(const double *const data, unsigned size);
double getDataStandardDeviation(const double *const data, double mean, unsigned size);

#endif
