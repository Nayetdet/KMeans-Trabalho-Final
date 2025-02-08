#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "pgm.h"
#include "dice.h"

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Erro: Use <outDirPath:string> <targetDirPath:string> <binarizedOutDirPath:string> <binarizedTargetDirPath:string>\n");
        exit(1);
    }
    
    DIR *outDirPath = opendir(argv[1]);
    DIR *targetDirPath = opendir(argv[2]);
    DIR *binarizedOutDirPath = opendir(argv[3]);
    DIR *binarizedTargetDirPath = opendir(argv[4]);
    if (!outDirPath || !targetDirPath || !binarizedOutDirPath || !binarizedTargetDirPath) {
        if (outDirPath) closedir(outDirPath);
        if (targetDirPath) closedir(targetDirPath);
        if (binarizedOutDirPath) closedir(binarizedOutDirPath);
        if (binarizedTargetDirPath) closedir(binarizedTargetDirPath);
        fprintf(stderr, "Erro: Falha ao ler os diretórios informados\n");
        exit(1);
    }
    
    double diceMean = 0;
    unsigned imgCount = 0;
    
    struct dirent *entry;
    while ((entry = readdir(outDirPath))) {
        char outPath[FILENAME_MAX];
        char targetPath[FILENAME_MAX];
        char binarizedOutPath[FILENAME_MAX];
        char binarizedTargetPath[FILENAME_MAX];

        snprintf(outPath, sizeof(outPath), "%s/%s", argv[1], entry->d_name);
        snprintf(targetPath, sizeof(targetPath), "%s/%s", argv[2], entry->d_name);
        snprintf(binarizedOutPath, sizeof(binarizedOutPath), "%s/%s", argv[3], entry->d_name);
        snprintf(binarizedTargetPath, sizeof(binarizedTargetPath), "%s/%s", argv[4], entry->d_name);

        PGM *outPgm = readPGM(outPath);
        PGM *targetPgm = readPGM(targetPath);
        if (!outPgm || !targetPgm) {
            freePGM(outPgm);
            freePGM(targetPgm);
            continue;
        }
        
        double dice = getDiceByBinarizingData(outPgm->data, targetPgm->data, targetPgm->width * targetPgm->height);
        diceMean += dice;
        imgCount++;
        
        printf("Comparando %s com %s | Coeficiente Dice: %.2lf\n", outPath, targetPath, dice);
        writePGM(outPgm, binarizedOutPath);
        writePGM(targetPgm, binarizedTargetPath);

        freePGM(outPgm);
        freePGM(targetPgm);
    }

    if (imgCount) {
        diceMean /= imgCount;
        printf("\nMédia dos coeficientes Dice: %.2lf\n", diceMean);
    } else {
        puts("Nenhuma imagem foi processada");
    }

    closedir(outDirPath);
    closedir(targetDirPath);
    closedir(binarizedOutDirPath);
    closedir(binarizedTargetDirPath);

    return 0;
}
