#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "pgm.h"
#include "histogram.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Erro: Use <inDirPath:string> <outDirPath:string>\n");
        exit(1);
    }
    
    DIR *inDir = opendir(argv[1]);
    if (!inDir) {
        fprintf(stderr, "Erro: Falha ao ler o diretório de entrada\n");
        exit(1);
    }

    DIR *outDir = opendir(argv[2]);
    if (!outDir) {
        fprintf(stderr, "Erro: Falha ao ler o diretório de saída\n");
        closedir(inDir);
        exit(1);
    }

    struct dirent *entry;
    unsigned char histogram[HISTOGRAM_SIZE] = {0};

    while ((entry = readdir(inDir))) {
        char inPath[FILENAME_MAX];
        if (snprintf(inPath, sizeof(inPath), "%s/%s", argv[1], entry->d_name) >= sizeof(inPath)) {
            continue;
        }

        char outPath[FILENAME_MAX];
        if (snprintf(outPath, sizeof(outPath), "%s/%s", argv[2], entry->d_name) >= sizeof(outPath)) {
            continue;
        }

        char *ext = strrchr(outPath, '.');
        if (ext && !strcmp(ext, ".pgm")) {
            *ext = '\0';
            unsigned long long outPathLength = strlen(outPath);
            if (snprintf(outPath + outPathLength, sizeof(outPath) - strlen(outPath), ".txt") >= sizeof(outPath) - outPathLength) {
                continue;
            }
        }

        PGM *inPgm = readPGM(inPath);
        if (!inPgm) {
            continue;
        }

        computeHistogram(inPgm->data, histogram, inPgm->width * inPgm->height);
        saveHistogram(outPath, histogram);
        free(inPgm);
    }

    closedir(inDir);
    closedir(outDir);

    return 0;
}
