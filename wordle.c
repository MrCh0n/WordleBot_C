#include <stdio.h>
#include <stdlib.h>
#include "WordleADT.h"

int main(){
    wordleADT wordle = newWordle();

    char word[] = "words";
    char guess[] = "rrrrr";

    addWords(wordle, word);

    choseWord(wordle);
    
    int dim = sizeWord(wordle);

    int estado[dim];

    checkWord(wordle, guess, estado, &dim);
    for(int i = 0; i < dim; i++){
        printf("%d ", estado[i]);
        }
    printf("\n");

    freeWordle(wordle);
    }
