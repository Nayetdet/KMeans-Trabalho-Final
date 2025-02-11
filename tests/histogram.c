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
#include "histogram.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Erro: Use <srcDirPath:string> <histogramsDirPath:string>\n");
        exit(1);
    }
    
    DIR *srcDir = opendir(argv[1]);
    DIR *histogramsDir = opendir(argv[2]);
    if (!srcDir || !histogramsDir) {
        if (srcDir) closedir(srcDir);
        if (histogramsDir) closedir(histogramsDir);
        fprintf(stderr, "Erro: Falha ao ler os diretórios informados\n");
        exit(1);
    }

    unsigned char histogram[UCHAR_MAX];
    struct dirent *entry;
    while ((entry = readdir(srcDir))) {
        char srcPath[FILENAME_MAX];
        char histogramsPath[FILENAME_MAX];
        
        snprintf(srcPath, sizeof(srcPath), "%s/%s", argv[1], entry->d_name);
        snprintf(histogramsPath, sizeof(histogramsPath), "%s/%s", argv[2], entry->d_name);

        char *fileExtension = strrchr(histogramsPath, '.');
        if (fileExtension && !strcmp(fileExtension, ".pgm")) {
            *fileExtension = '\0';
            unsigned long long histogramsPathLength = strlen(histogramsPath);
            snprintf(histogramsPath + histogramsPathLength, sizeof(histogramsPath) - histogramsPathLength, ".txt");
        }
        
        PGM *srcPgm = readPGM(srcPath);
        if (!srcPgm) {
            continue;
        }

        computeHistogram(histogram, srcPgm->data, srcPgm->width * srcPgm->height);
        writeHistogram(histogram, histogramsPath);
        freePGM(srcPgm);
    }

    closedir(srcDir);
    closedir(histogramsDir);

    return 0;
}
