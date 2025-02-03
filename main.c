#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

#include "kmeans.h"
#include "pgm.h"

#define IN_DIR_PATH "datasets"
#define OUT_DIR_PATH "out"

bool processImage(unsigned char k, unsigned maxIterations, const char *fileName);

int main(int argc, char **argv) {
    srand(time(NULL));
    clock_t begin = clock();

    if (argc != 3) {
        fprintf(stderr, "Erro: Use <k:unsigned> <maxIterations:unsigned>\n");
        exit(1);
    }

    DIR *dir = opendir(IN_DIR_PATH);
    if (!dir) {
        fprintf(stderr, "Erro: Falha ao ler o diretório informado\n");
        exit(1);
    }

    unsigned numImgs = 0;
    struct dirent *entry;

    while ((entry = readdir(dir))) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
            continue;
        }

        if (!processImage(atoi(argv[1]), atoi(argv[2]), entry->d_name)) {
            closedir(dir);
            exit(1);
        }

        numImgs++;
    }

    closedir(dir);
    double time = (double)(clock() - begin) / CLOCKS_PER_SEC;
    printf("Tempo total: %lf segundos\n", time);

    if (numImgs > 0) {
        printf("Tempo por imagem: %lf segundos\n", time / numImgs);
    } else {
        puts("Nenhuma imagem foi processada");
    }

    return 0;
}

bool processImage(unsigned char k, unsigned maxIterations, const char *fileName) {
    char inPath[256];
    snprintf(inPath, sizeof(inPath), "%s/%s", IN_DIR_PATH, fileName);
    printf("Processando: %s\n", inPath);

    PGM *pgm = readPGM(inPath);
    if (!pgm) {
        fprintf(stderr, "Erro: Falha ao ler a imagem de entrada\n");
        return false;
    }

    KMeansData kd = {
        .size = pgm->width * pgm->height,
        .maxValue = pgm->maxValue,
        .data = pgm->data
    };

    if (!applyKMeans(&kd, k, maxIterations)) {
        fprintf(stderr, "Erro: Falha ao aplicar o algoritmo k-means na imagem\n");
        freePGM(pgm);
        return false;
    }

    char outPath[256];
    snprintf(outPath, sizeof(outPath), "%s/out_%s", OUT_DIR_PATH, fileName);
    if (!writePGM(pgm, outPath)) {
        fprintf(stderr, "Erro: Falha ao salvar o arquivo\n");
        freePGM(pgm);
        return false;
    }

    freePGM(pgm);
    return true;
}
