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

#ifndef PGM_H
#define PGM_H

#include <stdbool.h>

typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned char maxValue;
    unsigned char *data;
} PGM;

PGM *readPGM(const char *const path);
bool writePGM(const PGM *const pgm, const char *const path);
void freePGM(PGM *pgm);

#endif
