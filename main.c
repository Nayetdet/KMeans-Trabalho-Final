#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

#include "kmeans.h"
#include "pgm.h"

static bool processImage(unsigned char k, unsigned maxIterations, const char *const inPath, const char *const outPath);

int main(int argc, char **argv) {
    srand(time(NULL));
    clock_t begin = clock();

    if (argc != 5) {
        fprintf(stderr, "Erro: Use <inDirPath:string> <outDirPath:string> <k:unsigned> <maxIterations:unsigned>\n");
        exit(1);
    }
    
    DIR *inDir = opendir(argv[1]);
    if (!inDir) {
        fprintf(stderr, "Erro: Falha ao ler o diretório de entrada\n");
        exit(1);
    }

    DIR *outDir = opendir(argv[2]);
    if (!outDir) {
        closedir(inDir);
        fprintf(stderr, "Erro: Falha ao ler o diretório de saída\n");
        exit(1);
    }

    unsigned numImgs = 0;
    struct dirent *entry;

    while ((entry = readdir(inDir))) {
        char inPath[FILENAME_MAX];
        if (snprintf(inPath, sizeof(inPath), "%s/%s", argv[1], entry->d_name) >= sizeof(inPath)) {
            continue;
        }

        char outPath[FILENAME_MAX];
        if (snprintf(outPath, sizeof(outPath), "%s/out_%s", argv[2], entry->d_name) >= sizeof(outPath)) {
            continue;
        }

        if (processImage(atoi(argv[3]), atoi(argv[4]), inPath, outPath)) {
            numImgs++;
        }
    }

    closedir(inDir);
    closedir(outDir);

    double time = (double)(clock() - begin) / CLOCKS_PER_SEC;
    printf("\nQuantidade de imagens: %u\n", numImgs);
    printf("Tempo total: %lf segundos\n", time);

    if (numImgs > 0) {
        printf("Tempo por imagem: %lf segundos\n", time / numImgs);
    } else {
        puts("Nenhuma imagem foi processada");
    }

    return 0;
}

static bool processImage(unsigned char k, unsigned maxIterations, const char *const inPath, const char *const outPath) {
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

    if (!writePGM(pgm, outPath)) {
        fprintf(stderr, "Erro: Falha ao salvar o arquivo\n");
        freePGM(pgm);
        return false;
    }

    freePGM(pgm);
    return true;
}
