#include <stdio.h>
#include <stdlib.h>
#include "WordleADT.h"
#include <string.h>

#define BITS 8

int main(){
    wordleADT wordle = newWordle();
    
    
    int dim = sizeWord(wordle);

    int estado[dim];

    //TODO interactuar con el usuario
    char guess[] = "verza";

    checkWord(wordle, guess, estado, &dim);
    for(int i = 0; i < dim; i++){
        printf("%d ", estado[i]);
        }
    printf("\n");

    freeWordle(wordle);
    }
