#include <stdio.h>

float dice_index(int clusters[], int clusters_size, int standards[], int standards_size);

int main (void) {

    int clusters[] = {2, 1, 1, 1, 1, 1, 2};
    int standards[] = {1, 1, 1, 1, 1, 1, 2};

    int clusters_size = sizeof(clusters) / sizeof(clusters[0]);
    int standards_size = sizeof(standards) / sizeof(standards[0]);

    float dice = dice_index(clusters, clusters_size, standards, standards_size);

    printf("Índice dice: %.2f\n", dice);

    return 0;
}


float dice_index(int clusters[], int clusters_size, int standards[], int standards_size) {
    int intersection = 0;

    for(int i = 0; i < clusters_size; i++) {
        if(clusters[i] == standards[i]) {
            intersection++;
        }
    }


    return (2.0 * intersection) / (clusters_size + standards_size);    
}