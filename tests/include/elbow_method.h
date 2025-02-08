#ifndef ELBOW_METHOD_H
#define ELBOW_METHOD_H

#include <stdbool.h>
#define MAX_ITERATIONS 256

void executeElbowMethod(const char *srcPath, unsigned maxK, unsigned long long *sseResults);
bool writeElbowMethod (const char *srcPath, unsigned long long *sseResults, unsigned maxK);

#endif
