#ifndef PGM_H
#define PGM_H

typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned char maxValue;
    unsigned char **data;
} PGM;

PGM *readPGM(const char *const path);
bool writePGM(const PGM *const pgm, const char *const path);
void freePGM(PGM *pgm);

#endif
