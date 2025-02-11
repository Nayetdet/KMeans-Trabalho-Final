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
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

#include "kmeans.h"
#include "pgm.h"

static bool processImage(const char *const initialPath, const char *const outPath, unsigned char k, unsigned maxIterations);

int main(int argc, char **argv) {
    srand(time(NULL));
    if (argc != 5) {
        fprintf(stderr, "Erro: Use <initialDirPath:string> <outDirPath:string> <k:unsigned char> <maxIterations:unsigned>\n");
        exit(1);
    }
    
    unsigned char k = (unsigned char)atoll(argv[3]);
    unsigned maxIterations = (unsigned)atoll(argv[4]);
     if (!k || !maxIterations) {
        fprintf(stderr, "Erro: Os valores de 'k' e de 'maxIterations' não podem ser zero\n");
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

        if (processImage(initialPath, outPath, k, maxIterations)) {
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

static bool processImage(const char *const initialPath, const char *const outPath, unsigned char k, unsigned maxIterations) {
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
