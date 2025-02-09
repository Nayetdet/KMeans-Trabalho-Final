#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>

#include "pgm.h"
#include "kmeans.h"
#include "metrics.h"
#include "elbow_method.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Erro: Use <initialPgmFilePath:string> <elbowDirPath:string> <kMax:unsigned char>\n");
        exit(1);
    }

    char *initialPgmFilePath = argv[1];
    char *elbowDirPath = argv[2];
    unsigned char kMax = atoi(argv[3]);

    DIR *elbowDir = opendir(elbowDirPath);
    if (!elbowDir) {
        fprintf(stderr, "Erro: Falha ao abrir o diretório do metódo do cotovelo\n");
        exit(1);
    }

    char *pgmFileName = strrchr(initialPgmFilePath, '/');
    if (!pgmFileName) {
        pgmFileName = initialPgmFilePath;
    }

    char elbowPath[FILENAME_MAX];
    snprintf(elbowPath, sizeof(elbowPath), "%s/%s", argv[2], pgmFileName);

    char *fileExtension = strrchr(elbowPath, '.');
    if (fileExtension && !strcmp(fileExtension, ".pgm")) {
        *fileExtension = '\0';
        unsigned long long elbowPathLength = strlen(elbowPath);
        snprintf(elbowPath + elbowPathLength, sizeof(elbowPath) - elbowPathLength, ".txt");
    }

    unsigned long long *sses = (unsigned long long *)malloc(kMax * sizeof(unsigned long long));
    if (!sses) {
        fprintf(stderr, "Erro: Falha ao alocar memória para os SSEs\n");
        closedir(elbowDir);
        exit(1);
    }

    calculateElbowMethod(sses, initialPgmFilePath, kMax);
    if (!writeElbowMethod(sses, elbowPath, kMax)) {
        free(sses);
        closedir(elbowDir);
        exit(1);
    }

    free(sses);
    closedir(elbowDir);
    return 0;
}
