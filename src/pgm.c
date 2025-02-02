#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
 
#include "pgm.h"

static void *cleanupOnError(FILE *fp, PGM *pgm);

PGM *readPGM(const char *const path) {
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        return NULL;
    }
    
    char format[3];
    PGM *pgm = (PGM *)malloc(sizeof(PGM));
    if (!pgm || fscanf(fp, "%2c\n", format) != 1 || strcmp(format, "P5")) {
        return cleanupOnError(fp, pgm);
    }
    
    char ch;
    while ((ch = fgetc(fp)) == '#')
        while ((ch = fgetc(fp)) != '\n' && ch != EOF);
    ungetc(ch, fp);
    
    if (fscanf(fp, "%u %u %hhu", &pgm->width, &pgm->height, &pgm->maxValue) != 3 || !pgm->width || !pgm->height) {
        return cleanupOnError(fp, pgm);
    }

    fgetc(fp);
    pgm->data = (unsigned char **)malloc(pgm->height * sizeof(unsigned char *));
    if (!pgm->data) {
        return cleanupOnError(fp, pgm);
    }

    for (unsigned int i = 0; i < pgm->height; i++) {
        pgm->data[i] = (unsigned char *)malloc(pgm->width * sizeof(unsigned char));
        if (!pgm->data[i]) {
            return cleanupOnError(fp, pgm);
        }

        if (fread(pgm->data[i], sizeof(unsigned char), pgm->width, fp) != pgm->width) {
            return cleanupOnError(fp, pgm);
        }
    }
    
    fclose(fp);
    return pgm;
}

bool writePGM(const PGM *const pgm, const char *const path) {
    FILE *fp = fopen(path, "wb");
    if (!fp) {
        return false;
    }
    
    fprintf(fp, "P5\n");
    fprintf(fp, "%u %u\n", pgm->width, pgm->height);
    fprintf(fp, "%hhu\n", pgm->maxValue);
    
    for (unsigned int i = 0; i < pgm->height; i++) {
        for (unsigned int j = 0; j < pgm->width; j++) {
            if (fwrite(&pgm->data[i][j], sizeof(unsigned char), 1, fp) != 1) {
                fclose(fp);
                return false;
            }
        }
    }
    
    fclose(fp);
    return true;
}

void freePGM(PGM *pgm) {
    if (!pgm) {
        return;
    }
    
    if (pgm->data) {
        for (unsigned int i = 0; i < pgm->height; i++) {
            free(pgm->data[i]);
        }

        free(pgm->data);
    }
    
    free(pgm);
}

static void *cleanupOnError(FILE *fp, PGM *pgm) {
    if (fp) {
        fclose(fp);
    }

    freePGM(pgm);
    return NULL;
}
