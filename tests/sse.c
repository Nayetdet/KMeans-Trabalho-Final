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
#include <string.h>
#include <dirent.h>
#include <time.h>

#include "sse.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    if (argc != 5) {
        fprintf(stderr, "Erro: Use <initialDirPath:string> <sseDirPath:string> <maxK:unsigned char> <maxIterations:unsigned>\n");
        exit(1);
    }

    unsigned char maxK = (unsigned char)atoll(argv[3]);
    unsigned maxIterations = (unsigned)atoll(argv[4]);

    DIR *initialDir = opendir(argv[1]);
    DIR *sseDir = opendir(argv[2]);
    if (!initialDir || !sseDir) {
        if (initialDir) closedir(initialDir);
        if (sseDir) closedir(sseDir);
        fprintf(stderr, "Erro: Falha ao ler os diretórios informados\n");
        exit(1);
    }

    struct dirent *entry;
    while ((entry = readdir(initialDir))) {
        char initialPath[FILENAME_MAX];
        char ssePath[FILENAME_MAX];

        snprintf(initialPath, sizeof(initialPath), "%s/%s", argv[1], entry->d_name);
        snprintf(ssePath, sizeof(ssePath), "%s/%s", argv[2], entry->d_name);

        char *fileExtension = strrchr(ssePath, '.');
        if (fileExtension && !strcmp(fileExtension, ".pgm")) {
            *fileExtension = '\0';
            unsigned long long elbowPathLength = strlen(ssePath);
            snprintf(ssePath + elbowPathLength, sizeof(ssePath) - elbowPathLength, ".txt");
        }

        unsigned long long *sses = getSSEs(initialPath, maxK, maxIterations);
        if (!sses) {
            continue;
        }

        writeSSEs(sses, ssePath, maxK);
        free(sses);
    }

    closedir(initialDir);
    closedir(sseDir);

    return 0;
}
