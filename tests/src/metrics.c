#include "metrics.h"

double calculateDice(const unsigned char *const a, const unsigned char *const b, unsigned size) {
    unsigned intersectionCount = 0;
    for (unsigned i = 0; i < size; i++) {
        if (a[i] == b[i]) {
            intersectionCount++;
        }
    }

    return (2.0 * intersectionCount) / (size + size);
}
