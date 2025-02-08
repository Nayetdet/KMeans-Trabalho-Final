#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h> 

#include "pgm.h"
#include "kmeans.h"
#include "sse.h"
#include "elbow_method.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Erro: Use <srcPath:string> <outDirPath:string> <maxK:int>\n");
        exit(1);
    }

    const char *srcPath = argv[1];
    const char *outDirPath = argv[2];
    unsigned maxK = atoi(argv[3]);


    DIR *outDir = opendir(outDirPath);
    if (!outDir) {
        fprintf(stderr, "Erro: Falha ao abrir o diretório de saída %s\n", outDirPath);
        exit(1);
    }

    struct stat st = {0};
    if (stat(outDirPath, &st) == -1) {
        if (mkdir(outDirPath, 0700) == -1) {
            fprintf(stderr, "Erro: Falha ao criar o diretório de saída %s\n", outDirPath);
            closedir(outDir);
            exit(1);
        }
    }

    char outPath[FILENAME_MAX];
    snprintf(outPath, sizeof(outPath), "%s/%s_sse.txt", outDirPath, strrchr(srcPath, '/') + 1);

    unsigned long long sseResults[maxK];

    executeElbowMethod(srcPath, maxK, sseResults);

    if (!writeElbowMethod(outPath, sseResults, maxK)) {
        fprintf(stderr, "Erro ao salvar os resultados SSE para %s\n", outPath);
    }

    closedir(outDir);

    return 0;
}
