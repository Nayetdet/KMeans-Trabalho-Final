#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "pgm.h"
#include "metrics.h"

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
    double diceMean = 0.0;
    unsigned count = 0;

    while ((entry = readdir(inDir))) {
        char inPath[FILENAME_MAX];
        if (snprintf(inPath, sizeof(inPath), "%s/%s", argv[1], entry->d_name) >= sizeof(inPath)) {
            continue;
        }

        char outPath[FILENAME_MAX];
        if (snprintf(outPath, sizeof(outPath), "%s/out_%s", argv[2], entry->d_name) >= sizeof(outPath)) {
            continue;
        }

        PGM *inPgm = readPGM(inPath);
        PGM *outPgm = readPGM(outPath);
        if (!inPgm || !outPgm) {
            free(inPgm);
            free(outPgm);
            continue;
        }

        double dice = calculateDice(inPgm->data, outPgm->data, outPgm->width * outPgm->height);
        printf("Comparando %s com %s | Coeficiente Dice: %.2lf\n", inPath, outPath, dice);

        diceMean += dice;
        count++;

        free(inPgm);
        free(outPgm);
    }

    diceMean /= count;
    printf("\nMédia dos coeficientes Dice: %.2lf\n", diceMean);

    closedir(inDir);
    closedir(outDir);

    return 0;
}
