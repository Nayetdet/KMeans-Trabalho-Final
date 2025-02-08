#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>

#include "pgm.h"
#include "histogram.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Erro: Use <initialDirPath:string> <histogramsDirPath:string>\n");
        exit(1);
    }
    
    DIR *initialDir = opendir(argv[1]);
    DIR *histogramsDir = opendir(argv[2]);
    if (!initialDir || !histogramsDir) {
        if (initialDir) closedir(initialDir);
        if (histogramsDir) closedir(histogramsDir);
        fprintf(stderr, "Erro: Falha ao ler os diretórios informados\n");
        exit(1);
    }

    unsigned char histogram[UCHAR_MAX];
    struct dirent *entry;
    while ((entry = readdir(initialDir))) {
        char initialPath[FILENAME_MAX];
        char histogramsPath[FILENAME_MAX];
        
        snprintf(initialPath, sizeof(initialPath), "%s/%s", argv[1], entry->d_name);
        snprintf(histogramsPath, sizeof(histogramsPath), "%s/%s", argv[2], entry->d_name);

        char *ext = strrchr(histogramsPath, '.');
        if (ext && !strcmp(ext, ".pgm")) {
            *ext = '\0';
            unsigned long long histogramsPathLength = strlen(histogramsPath);
            snprintf(histogramsPath + histogramsPathLength, sizeof(histogramsPath) - histogramsPathLength, ".txt");
        }

        PGM *initialPgm = readPGM(initialPath);
        if (!initialPgm) {
            continue;
        }

        computeHistogram(histogram, initialPgm->data, initialPgm->width * initialPgm->height);
        writeHistogram(histogram, histogramsPath);
        freePGM(initialPgm);
    }

    closedir(initialDir);
    closedir(histogramsDir);

    return 0;
}
