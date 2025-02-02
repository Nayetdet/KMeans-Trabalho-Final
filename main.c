#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "kmeans.h"
#include "pgm.h"

int main(int argc, char **argv) {
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

    srand(time(NULL));
    if (!applyKMeans((KMeansData *)pgm, k, maxIterations)) {
        fprintf(stderr, "Erro: Falha ao executar o algoritmo k-means\n");
        freePGM(pgm);
        exit(1);
    }
    
    if (!writePGM(pgm, imgOutPath)) {
        fprintf(stderr, "Erro: Falha ao salvar o arquivo\n");
        freePGM(pgm);
        exit(1);
    }

    puts("Sucesso!");
    freePGM(pgm);
    return 0;
}
