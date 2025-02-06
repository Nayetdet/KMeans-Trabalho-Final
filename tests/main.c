#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "pgm.h"
#include "metrics.h"

#define PATH_MAX_SIZE 256

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
        closedir(inDir);
        fprintf(stderr, "Erro: Falha ao ler o diretório de saída\n");
        exit(1);
    }

    struct dirent *entry;
    while ((entry = readdir(inDir))) {
        char inPath[PATH_MAX_SIZE];
        if (snprintf(inPath, sizeof(inPath), "%s/%s", argv[1], entry->d_name) >= sizeof(inPath)) {
            continue;
        }

        PGM *inPgm = readPGM(inPath);
        if (!inPgm) {
            continue;
        }

        char outPath[PATH_MAX_SIZE];
        if (snprintf(outPath, sizeof(outPath), "%s/%s", argv[2], entry->d_name) >= sizeof(outPath)) {
            continue;
        }

        PGM *outPgm = readPGM(outPath);
        if (!outPgm) {
            free(inPgm);
            continue;
        }

        double dice = calculateDice(inPgm->data, outPgm->data, outPgm->width * outPgm->height);
        printf("Comparando \"%s\" com \"%s\" | Coeficiente Dice: %.2lf\n", inPath, outPath, dice);
        
        free(inPgm);
        free(outPgm);
    }

    closedir(inDir);
    closedir(outDir);

    return 0;
}
