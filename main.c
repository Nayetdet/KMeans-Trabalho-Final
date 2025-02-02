#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "kmeans.h"
#include "pgm.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    if (argc != 5) {
        fprintf(stderr, "Use: <k:unsigned> <maxIterations:unsigned> <imgInPath:string> <imgOutPath:string>\n");
        exit(1);
    }

    unsigned k = atoi(argv[1]);
    unsigned maxIterations = atoi(argv[2]);
    char *imgInPath = argv[3];
    char *imgOutPath = argv[4];

    PGM *pgm = readPGM(imgInPath);
    if (!pgm) {
        fprintf(stderr, "Erro: Falha ao ler a imagem de entrada\n");
        exit(1);
    }
    
    KMeansData kd = {
        .size = pgm->width * pgm->height,
        .maxValue = pgm->maxValue,
        .data = pgm->data
    };

    if (!applyKMeans(&kd, k, maxIterations)) {
        fprintf(stderr, "Erro: Falha ao aplicar o algoritmo k-means na imagem\n");
        freePGM(pgm);
        exit(1);
    }

    if (!writePGM(pgm, imgOutPath)) {
        fprintf(stderr, "Erro: Falha ao salvar o arquivo\n");
        freePGM(pgm);
        exit(1);
    }

    puts("A imagem foi processada e salva com sucesso!");
    freePGM(pgm);
    return 0;
}
