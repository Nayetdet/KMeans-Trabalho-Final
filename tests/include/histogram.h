#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <stdbool.h>
#include <limits.h>

void computeHistogram(unsigned char histogram[UCHAR_MAX], const unsigned char *const data, unsigned size);
bool writeHistogram(unsigned char histogram[UCHAR_MAX], const char *const histogramsPath);

#endif
