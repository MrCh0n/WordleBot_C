#include <stdio.h>
#include <stdlib.h>
#include "WordleADT.h"

#define JUEGOS 6

int main(){
    wordleADT wordle = newWordle();
    
    
    int dim;
    info *data;

    makeResult(wordle);

    data = getInfo(wordle, &dim);
    for (int i=0; i<10; i++){
        printf("palabra: %s, info: %f \n", data[i].word, data[i].info);
        }
    for(int i = 0; i < dim; i++){
        free(data[i].word);
        }
    free(data);

    freeWordle(wordle);
}
