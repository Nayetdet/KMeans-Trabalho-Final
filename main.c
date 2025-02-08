#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

#include "kmeans.h"
#include "pgm.h"

static bool processImage(unsigned char k, unsigned maxIterations, const char *const initialPath, const char *const outPath);

int main(int argc, char **argv) {
    srand(time(NULL));
    if (argc != 5) {
        fprintf(stderr, "Erro: Use <initialDirPath:string> <outDirPath:string> <k:unsigned> <maxIterations:unsigned>\n");
        exit(1);
    }
    
    DIR *initialDir = opendir(argv[1]);
    DIR *outDir = opendir(argv[2]);
    if (!initialDir || !outDir) {
        if (initialDir) closedir(initialDir);
        if (outDir) closedir(outDir);
        fprintf(stderr, "Erro: Falha ao ler os diretórios informados\n");
        exit(1);
    }
    
    clock_t begin = clock();
    unsigned imgCount = 0;

    struct dirent *entry;
    while ((entry = readdir(initialDir))) {
        char initialPath[FILENAME_MAX];
        char outPath[FILENAME_MAX];

        snprintf(initialPath, sizeof(initialPath), "%s/%s", argv[1], entry->d_name);
        snprintf(outPath, sizeof(outPath), "%s/%s", argv[2], entry->d_name);

        if (processImage(atoi(argv[3]), atoi(argv[4]), initialPath, outPath)) {
            imgCount++;
        }
    }

    closedir(initialDir);
    closedir(outDir);

    double time = (double)(clock() - begin) / CLOCKS_PER_SEC;
    printf("\nQuantidade de imagens: %u\n", imgCount);
    printf("Tempo total: %lf segundos\n", time);

    if (imgCount > 0) {
        printf("Tempo por imagem: %lf segundos\n", time / imgCount);
    } else {
        puts("Nenhuma imagem foi processada");
    }

    return 0;
}

static bool processImage(unsigned char k, unsigned maxIterations, const char *const initialPath, const char *const outPath) {
    printf("Processando: %s\n", initialPath);

    PGM *pgm = readPGM(initialPath);
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
