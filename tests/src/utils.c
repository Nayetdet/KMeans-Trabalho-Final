// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
// * Aluno: João Pedro Moreira Campos de Lima              *
// * Matrícula: 20241045050391                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
// * Aluno: Isaac da Cunha Cavalcanti Duarte               *
// * Matrícula: 20241045050375                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
// * Aluno: Josué Rodrigues Avelino                        *
// * Matrícula: 20241045050219                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
// * Aluno: Orleoncio Maciel                               *
// * Matrícula: 20181045050165                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗

#include <limits.h>
#include <math.h>

#include "utils.h"

void binarizeData(unsigned char *data, unsigned size, unsigned char value) {
    for (unsigned i = 0; i < size; i++) {
        data[i] = (data[i] == value) ? UCHAR_MAX : 0;
    }
}

unsigned char getLowestValue(const unsigned char *const data, unsigned size) {
    unsigned char min = UCHAR_MAX;
    for (unsigned i = 0; i < size; i++) {
        if (min > data[i]) {
            min = data[i];
        }
    }

    return min;
}

double getMean(const double *const data, unsigned size) {
    if (!size) {
        return -1;
    }

    double sum = 0;
    for (unsigned i = 0; i < size; i++) {
        sum += data[i];
    }

    return sum / size;
}

double getStandardDeviation(const double *const data, double mean, unsigned size) {
    if (!size) {
        return -1;
    }

    double variation = 0;
    for (unsigned i = 0; i < size; i++) {
        variation += (data[i] - mean) * (data[i] - mean);
    }

    return sqrt(variation / size);
}
