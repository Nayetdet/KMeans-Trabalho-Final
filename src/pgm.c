#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "pgm.h"

PGM *readPGM(const char *const path) {
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        return NULL;
    }

    char format[3];
    if (fscanf(fp, "%2c\n", format) != 1 || strcmp(format, "P5")) {
        fclose(fp);
        return NULL;
    }

    char ch;
    while ((ch = fgetc(fp)) == '#')
        while ((ch = fgetc(fp)) != '\n' && ch != EOF);
    ungetc(ch, fp);

    PGM *pgm = (PGM *)malloc(sizeof(PGM));
    if (!pgm || fscanf(fp, "%u %u %hhu", &pgm->width, &pgm->height, &pgm->maxValue) != 3 || !pgm->width || !pgm->height) {
        free(pgm);
        fclose(fp);
        return NULL;
    }

    pgm->data = (unsigned char *)malloc(pgm->width * pgm->height * sizeof(unsigned char));
    if (!pgm->data || fread(pgm->data, sizeof(unsigned char), pgm->width * pgm->height, fp) != pgm->width * pgm->height) {
        free(pgm);
        fclose(fp);
        return NULL;
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

    if (fwrite(pgm->data, sizeof(unsigned char), pgm->width * pgm->height, fp) != pgm->width * pgm->height) {
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

    free(pgm->data);
    free(pgm);
}
