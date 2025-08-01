#include <stdio.h>
#include <stdlib.h>
#include "WordleADT.h"
#include <string.h>

#define JUEGOS 6

#define WHITE_TEXT    "\x1B[37m"
#define YELLOW_TEXT   "\x1B[33m"
#define GREEN_TEXT    "\x1B[32m"
#define RED_TEXT      "\x1B[31m"
#define RESET_COLOUR  "\x1B[0m"

int main(){
    wordleADT wordle = newWordle();
    
    
    int dim = sizeWord(wordle);

    int estado[dim];

    char guess[2*dim];
    int contador = 0;
    
    printf("Cantidad de letras: %d\n", dim);
    while(contador < JUEGOS){
        int flag;
        do{
            printf("Ingrese su opcion:");
            scanf("%s", guess);
            if(!(flag = checkWord(wordle, guess, estado))){
                printf("Palabra invalida\n");
                }
        }while(!flag);

        for(int i = 0; i < dim; i++){

            switch (estado[i]) {
                case GREY:
                  printf("%s%c%s ", WHITE_TEXT, guess[i], RESET_COLOUR);
                  break;
                case YELLOW:
                  printf("%s%c%s ", YELLOW_TEXT, guess[i], RESET_COLOUR);
                  break;
                case GREEN:
                  printf("%s%c%s ", GREEN_TEXT, guess[i], RESET_COLOUR);
                  break;
                default:
                  printf("%sE%s ", RED_TEXT, RESET_COLOUR);
                  break;
                }

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
