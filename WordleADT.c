#include "WordleADT.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>


#define LETTERS ('z'-'a'+1)
#define IDX (word[0]-'a');
#define RANDOM (double)(rand()/((double)RAND_MAX+1))
#define ABS(c) ((c) > 0 ? (c):(-(c)))

typedef struct words{
    char *word;
    struct words *tail;
    }words;

typedef struct wordleCDT{
    words *dicc[LETTERS];
    size_t letterCount[LETTERS];
    
    size_t wordCount;
    size_t wordlen;

    int **results;

    char *chosenWord;
    }CDT;

wordleADT newWordle(){
    srand(time(NULL));
    return calloc(1,sizeof(CDT));
    }

int sizeWord(wordleADT wordle){
    return wordle->wordlen;
    }

words *addWordrec(words *list, char *word, int *flag, size_t len){
    int c;
    if(list == NULL || (c = strcmp(word, list->word)) < 0){
        words *aux = malloc(sizeof(words));

        aux->tail = list;
        aux->word = strcpy(malloc(len), word);
        return aux;
        }
    if(c == 0){
        return list;
        }
    list->tail = addWordrec(list->tail, word, flag, len);
    return list;
    }

//TODO decidir si devuelve algo
int addWords(wordleADT wordle, char *word){
    int flag = 1;
    int idx = IDX;

    if (wordle->wordlen == 0){
        wordle->wordlen = strlen(word) +1;
        }

    wordle->dicc[idx] = addWordrec(wordle->dicc[idx], word, &flag, wordle->wordlen);
    
    wordle->letterCount[idx] += flag;
    wordle->wordCount += flag;
    return flag;
    }

int choseWord(wordleADT wordle){
    int idx = RANDOM * (LETTERS-1);
    
    while(wordle->letterCount[idx] == 0){
        idx = RANDOM * (LETTERS-1);
        }

    int cantidad = RANDOM * wordle->letterCount[idx];
    
    words *aux = wordle->dicc[idx];

    while(cantidad > 0){
        aux = aux->tail;
        cantidad--;
        }
    
    wordle->chosenWord = strcpy(malloc(wordle->wordlen), aux->word);
    return 1;//TODO que poner en return
    }
/*
int **makeResult(int size){
    if(wordle->results == NULL){
        wordle->results = makeResult(size);
        }
    return NULL;
    }
TODO por si se hace el bot
*/

int check(int i, int size, char *word, char *guess){
    for (int j = 0; j < size; j++){
        if((guess[i]-word[j]) == 0){
            word[j] -= guess[i];
            return ABS(i-j);
            }
        }
    return -1;
    }

int checkWord(wordleADT wordle, char *guess, int *estado, int *dim){
    int total = 0;

    int size = wordle->wordlen-1;
    *dim = size;
    
    char word[size];
    for(int i = 0; i<size; i++){
        word[i] = wordle->chosenWord[i];
        }

    int c;
    for (int i = 0; i < size; i++){
        if((c = check(i, size, word, guess)) < 0){
            estado[i] = GREY;
            total += GREY;
            }
        if(c > 0){
            estado[i] = YELLOW;
            total += YELLOW;
            }
        if(c == 0) {
            estado[i] = GREEN;
            total += GREEN;
            }
        }

    if(total == size*GREEN){
        return 1;
        }

    return -1;
    }

void freeWords(words *list){
    if(list == NULL){
        return;
        }
    freeWords(list->tail);
    free(list->word);
    free(list);
    }

void freeWordle(wordleADT wordle){
    for(int i = 0; i < LETTERS; i++){
        freeWords(wordle->dicc[i]);
        }
    free(wordle->chosenWord);
    free(wordle);
    }
