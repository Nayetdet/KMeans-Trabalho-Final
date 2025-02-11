// *********************************************************
// * Aluno: João Pedro Moreira Campos de Lima              *
// * Matrícula: 20241045050391                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
// * Aluno: Isaac da Cunha Cavalcanti Duarte               *
// * Matrícula: 20241045050375                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
// * Aluno: Josué Rodrigues Avelino                        *
// * Matrícula: 20241045050219                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
// * Aluno: Orleoncio Maciel                               *
// * Matrícula: 20181045050165                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************

#include <stdio.h>
#include <stdbool.h>

#include "histogram.h"

void computeHistogram(unsigned char histogram[UCHAR_MAX], const unsigned char *const data, unsigned size) {
    for (unsigned i = 0; i < UCHAR_MAX; i++) {
        histogram[i] = 0;
    }
    
    for (unsigned i = 0; i < size; i++) {
        histogram[data[i]]++;
    }
}

bool writeHistogram(unsigned char histogram[UCHAR_MAX], const char *const histogramsPath) {
    FILE *fp = fopen(histogramsPath, "w");
    if (!fp) {
        fprintf(stderr, "Erro: Falha ao abrir o arquivo para escrita\n");
        return false;
    }

    for (unsigned i = 0; i < UCHAR_MAX; i++) {
        fprintf(fp, "%u ", histogram[i]);      
    }
    
    printf("Histograma salvo em: %s\n", histogramsPath);
    fclose(fp);
    return true;
}
