#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "kmeans.h"
#include "pgm.h"

int main(void) {
    srand(time(NULL));
    PGM *pgm = readPGM("assets/smurf.pgm");
    if (!pgm) {
        fprintf(stderr, "Erro: Falha ao ler a imagem\n");
        exit(1);
    }

    KMeansData km;
    km.size = pgm->width * pgm->height;
    km.maxValue = pgm->maxValue;
    km.data = pgm->data;

    if (!getKMeans(&km, 3, 100)) {
        fprintf(stderr, "Erro: Falha ao executar o algoritmo k-means\n");
        freePGM(pgm);
        exit(1);
    }

    if (!writePGM(pgm, "assets/smurf_out.pgm")) {
        fprintf(stderr, "Erro: Falha ao salvar o arquivo\n");
        freePGM(pgm);
        exit(1);
    }

    puts("Sucesso!");
    freePGM(pgm);
    return 0;
}