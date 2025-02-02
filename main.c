#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <limits.h>

#include "kmeans.h"
#include "pgm.h"

bool processImage(const char *path, unsigned k, unsigned maxIterations);
unsigned processDirectory(const char *dirPath, unsigned k, unsigned maxIterations);

int main(int argc, char **argv) {
    srand(time(NULL));
    if (argc != 4) {
        fprintf(stderr, "Erro: Use <k:unsigned> <maxIterations:unsigned> <datasetsDirPath:string>\n");
        exit(1);
    }

    unsigned k = atoi(argv[1]);
    unsigned maxIterations = atoi(argv[2]);
    const char *dirPath = argv[3];

    clock_t begin = clock();
    unsigned numImgs = processDirectory(dirPath, k, maxIterations);
    clock_t end = clock();

    double totalTime = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo Total: %lf segundos\n", totalTime);

    if (numImgs > 0) {
        printf("Tempo por imagem: %lf segundos\n", totalTime / numImgs);
    } else {
        puts("Nenhuma imagem foi processada");
    }

    return 0;
}

unsigned processDirectory(const char *dirPath, unsigned k, unsigned maxIterations) {
    DIR *dir = opendir(dirPath);
    if (!dir) {
        fprintf(stderr, "Erro: Falha ao ler o diretório informado\n");
        exit(1);
    }

    struct dirent *entry;
    unsigned numImgs = 0;

    while ((entry = readdir(dir))) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
            continue;
        }

        char imgPath[PATH_MAX];
        snprintf(imgPath, sizeof(imgPath), "%s/%s", dirPath, entry->d_name);

        if (!processImage(imgPath, k, maxIterations)) {
            closedir(dir);
            exit(1);
        }

        numImgs++;
    }

    closedir(dir);
    return numImgs;
}

bool processImage(const char *imgPath, unsigned k, unsigned maxIterations) {
    printf("Processando: %s\n", imgPath);

    PGM *pgm = readPGM(imgPath);
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

    freePGM(pgm);
    return true;
}
