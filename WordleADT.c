#include "WordleADT.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define LETTERS ('z'-'a'+1)
#define MAXBUFFER 16
#define IDX (word[0]-'a');
#define RANDOM (double)(rand()/((double)RAND_MAX+1))

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

    int cantidad = wordle->letterCount[idx];
    
    words *aux = wordle->dicc[idx];

    while(cantidad > 0){
        aux = aux->tail;
        cantidad--;
        }
    
    wordle->chosenWord = strcpy(malloc(wordle->wordlen), aux->word);
    return 1;//TODO que poner en return
    }

int **makeResult(int size){
    return NULL;
    }

int checkWord(wordleADT wordle, char *guess, int estado[]){
    int size = wordle->wordlen;
    if(wordle->results == NULL){
        wordle->results = makeResult(size);
        }

    //TODO checkear la guess

    return size;
    }
