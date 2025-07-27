#include <stdio.h>
#include <stdlib.h>
#include "WordleADT.h"
#include <string.h>

#define BITS 8

int main(){
    wordleADT wordle = newWordle();
    
    char guess[] = "verza";

 //   addWords(wordle, word);

   // choseWord(wordle);
    
    int dim = sizeWord(wordle);

    int estado[dim];

    checkWord(wordle, guess, estado, &dim);
    for(int i = 0; i < dim; i++){
        printf("%d ", estado[i]);
        }
    printf("\n");

    freeWordle(wordle);
    }
