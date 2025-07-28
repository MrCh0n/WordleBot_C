#include <stdio.h>
#include <stdlib.h>
#include "WordleADT.h"
#include <string.h>

#define JUEGOS 6

int main(){
    wordleADT wordle = newWordle();
    
    
    int dim = sizeWord(wordle);

    makeResult(wordle);

    freeWordle(wordle);
}
