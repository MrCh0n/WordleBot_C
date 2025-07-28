#include <stdio.h>
#include <stdlib.h>
#include "WordleADT.h"
#include <string.h>

#define JUEGOS 6

int main(){
    wordleADT wordle = newWordle();
    
    
    int dim = sizeWord(wordle);

    int estado[dim];

    char guess[2*dim];
    int contador = 0;
    
    makeResult(wordle);

    printf("Cantidad de letras: %d\n", dim);
    while(contador < JUEGOS){
        int flag;
        do{
            printf("Ingrese su opcion:");
            scanf("%s", guess);
            if(flag = (strlen(guess) != dim)){
                printf("Cantidad invalida de letras\n");
                }
        }while(flag);

        flag = checkWord(wordle, guess, estado);

        for(int i = 0; i < dim; i++){
            printf("%d ", estado[i]);
            }
        printf("\n");
        
        if(flag > 0){
            contador = JUEGOS;
            printf("Felicidades por ganar\n");
            }

        contador++;

        if(contador >= JUEGOS && flag < 0){
            char *word = getWord(wordle);
            printf("Perdio\nLa palabra era: %s\n", word);
            free(word);
            }
        }
    freeWordle(wordle);
    }
