#include <limits.h>

#include "dice.h"

double getDiceByBinarizingData(unsigned char *outData, unsigned char *targetData, unsigned size) {
    unsigned targetCount = 0;
    unsigned char outMin = UCHAR_MAX;
    for (unsigned i = 0; i < size; i++) {
        if (targetData[i] == CELL_NUCLEUS_COLOR) {
            targetData[i] = UCHAR_MAX;
            targetCount++;
        } else {
            targetData[i] = 0;
        }
        
        if (outMin > outData[i]) {
            outMin = outData[i];
        }
    }
    
    unsigned outCount = 0;
    unsigned intersectionCount = 0;
    for (unsigned i = 0; i < size; i++) {
        if (outData[i] == outMin) {
            if (targetData[i]) {
                intersectionCount++;
            }
            
            outData[i] = UCHAR_MAX;
            outCount++;
        } else {
            outData[i] = 0;
        }
    }

    if (!(outCount + targetCount)) {
        return -1;
    }
    
    return (2.0 * intersectionCount) / (outCount + targetCount);
}
