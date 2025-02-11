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
#include <string.h>
#include <dirent.h>

#include "pgm.h"
#include "dice.h"
#include "utils.h"

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Erro: Use <outDirPath:string> <targetDirPath:string> <binarizedOutDirPath:string> <binarizedTargetDirPath:string>\n");
        exit(1);
    }

    unsigned imgCapacity = 100;
    double *dices = (double *)malloc(imgCapacity * sizeof(double));
    if (!dices) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o programa\n");
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

    unsigned imgCount = 0;

    struct dirent *entry;
    while ((entry = readdir(outDirPath))) {
        if (imgCount >= imgCapacity) {
            imgCapacity += 50;
            double *tmp = (double *)realloc(dices, imgCapacity * sizeof(double));
            if (!tmp) {
                free(dices);
                closedir(outDirPath);
                closedir(targetDirPath);
                closedir(binarizedOutDirPath);
                closedir(binarizedTargetDirPath);
                fprintf(stderr, "Erro: Falha ao realocar memória para o programa\n");
                exit(1);
            }

            dices = tmp;
        }

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

        binarizeData(outPgm->data, outPgm->width * outPgm->height, getLowestDataValue(outPgm->data, outPgm->width * outPgm->height));
        binarizeData(targetPgm->data, targetPgm->width * targetPgm->height, CELL_NUCLEUS_COLOR);
        
        dices[imgCount] = getDice(outPgm->data, targetPgm->data, targetPgm->width * targetPgm->height);
        printf("Comparando %s com %s | Coeficiente Dice: %.2lf\n", outPath, targetPath, dices[imgCount]);
        imgCount++;
        
        writePGM(outPgm, binarizedOutPath);
        writePGM(targetPgm, binarizedTargetPath);
        
        freePGM(outPgm);
        freePGM(targetPgm);
    }

    if (imgCount) {
        double mean = getDataMean(dices, imgCount);
        printf("\nMédia dos coeficientes Dice: %.2lf\n", mean);
        printf("Desvio padrão dos coeficientes Dice: %.2lf\n", getDataStandardDeviation(dices, mean, imgCount));
    } else {
        puts("Nenhuma imagem foi processada");
    }

    free(dices);
    closedir(outDirPath);
    closedir(targetDirPath);
    closedir(binarizedOutDirPath);
    closedir(binarizedTargetDirPath);

    return 0;
}
