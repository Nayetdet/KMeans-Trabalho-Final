#ifndef ELBOW_METHOD_H
#define ELBOW_METHOD_H

#include <stdbool.h>

void calculateElbowMethod(unsigned long long *sses, const char *const initialPgmFilePath, unsigned char kMax);
bool writeElbowMethod (const unsigned long long *const sses, const char *const elbowPath, unsigned char kMax);

#endif
