#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "pgm.h"
#include "dice.h"

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
    while ((entry = readdir(inDir))) {
        char inPath[FILENAME_MAX];
        if (snprintf(inPath, sizeof(inPath), "%s/%s", argv[1], entry->d_name) >= sizeof(inPath)) {
            continue;
        }
        
        char outPath[FILENAME_MAX];
        if (snprintf(outPath, sizeof(outPath), "%s/%s", argv[2], entry->d_name) >= sizeof(outPath)) {
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
        printf("Comparando \"%s\" com \"%s\" | Coeficiente Dice: %.2lf\n", inPath, outPath, dice);

        free(inPgm);
        free(outPgm);
    }

    closedir(inDir);
    closedir(outDir);

    return 0;
}
