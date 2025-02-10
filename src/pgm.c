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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "pgm.h"

static void *cleanupPGMOnError(FILE *fp, PGM *pgm);

PGM *readPGM(const char *const path) {
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        return NULL;
    }

    char format[3];
    PGM *pgm = (PGM *)malloc(sizeof(PGM));
    if (!pgm || fscanf(fp, "%2c\n", format) != 1 || strcmp(format, "P5")) {
        return cleanupPGMOnError(fp, pgm);
    }

    char ch;
    while ((ch = fgetc(fp)) == '#') {
        while ((ch = fgetc(fp)) != '\n' && ch != EOF);
    }
    
    ungetc(ch, fp);
    if (fscanf(fp, "%u %u %hhu", &pgm->width, &pgm->height, &pgm->maxValue) != 3) {
        return cleanupPGMOnError(fp, pgm);
    }

    fgetc(fp);
    unsigned long long size = pgm->width * pgm->height;
    if (!size || !(pgm->data = (unsigned char *)malloc(size * sizeof(unsigned char)))) {
        return cleanupPGMOnError(fp, pgm);
    }

    if (fread(pgm->data, sizeof(unsigned char), size, fp) != size) {
        return cleanupPGMOnError(fp, pgm);
    }

    fclose(fp);
    return pgm;
}

bool writePGM(const PGM *const pgm, const char *const path) {
    if (!pgm || !pgm->data) {
        return false;
    }

    FILE *fp = fopen(path, "wb");
    if (!fp) {
        return false;
    }

    fprintf(fp, "P5\n");
    fprintf(fp, "%u %u\n", pgm->width, pgm->height);
    fprintf(fp, "%hhu\n", pgm->maxValue);

    unsigned long long size = pgm->width * pgm->height;
    if (!size || fwrite(pgm->data, sizeof(unsigned char), size, fp) != size) {
        fclose(fp);
        return false;
    }
    
    fclose(fp);
    return true;
}

void freePGM(PGM *pgm) {
    if (!pgm) {
        return;
    }

    if (pgm->data) {
        free(pgm->data);
        pgm->data = NULL;
    }

    free(pgm);
}

static void *cleanupPGMOnError(FILE *fp, PGM *pgm) {
    if (fp) {
        fclose(fp);
    }

    freePGM(pgm);
    return NULL;
}
