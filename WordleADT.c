#include "WordleADT.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

//TODO funcion de eliminar palabras incogruentes

#define FILENAME "possible_solutions.txt"
//#define FILENAME "words.txt"
#define BITS 8

#define BLOCK 64

#define LETTERS ('z'-'a'+1)
#define RANDOM (double)(rand()/((double)RAND_MAX+1))
#define ABS(c) ((c) > 0 ? (c):(-(c)))
#define EPSILON 0.05

//status es 1 o 0 por si la palabra es posible o no
typedef struct words{
    char *word;
    int status;
    }words;

typedef struct infoL{
    struct info data;
    struct infoL *tail;
    }infoL;

typedef struct wordleCDT{
    words *dicc;
    size_t reserved;

    size_t wordCount;
    size_t actualCount;
    size_t wordlen;

    int **results;

    char *chosenWord;
    }CDT;

int addFile(wordleADT wordle, char *filename);

int choseWord(wordleADT wordle);

wordleADT newWordle(){
    srand(time(NULL));

    wordleADT aux = calloc(1,sizeof(CDT));
    
    addFile(aux, FILENAME);

    choseWord(aux);

    return aux;
    }

int sizeWord(wordleADT wordle){
    return wordle->wordlen - 1;
    }

char *getWord(wordleADT wordle){
    return strcpy(malloc(wordle->wordlen), wordle->chosenWord);
    }

//TODO decidir si devuelve algo
int addWords(wordleADT wordle, char *word){
    int flag = 1;
    
    if(wordle->wordCount >= wordle->reserved){
        wordle->reserved += BLOCK;
        wordle->dicc = realloc(wordle->dicc, sizeof(words)*wordle->reserved);
        }

    wordle->dicc[wordle->wordCount].word = strcpy(malloc(wordle->wordlen), word);
    wordle->dicc[wordle->wordCount].status = 1;
    wordle->wordCount += 1;

    return flag;
    }

//parsea filename para conseguir las palabras
int addFile(wordleADT wordle, char *filename){
    FILE *file = fopen(filename, "r");//TODO cheackear fopen
    char word[BITS];

    char *p;

    if((p = fgets(word, BITS, file)) == NULL){
        //TODO esta vacio
        }

    wordle->wordlen = strlen(word);

    while(p != NULL){
        word[wordle->wordlen - 1] = '\0';
        addWords(wordle, word);

        p = fgets(word, BITS, file);
        }

    wordle->dicc = realloc(wordle->dicc, wordle->wordCount*sizeof(words));

    wordle->actualCount = wordle->wordCount;

    fclose(file);
    return 1;
    }

//elije una palabra del vector dicc y la guarda
int choseWord(wordleADT wordle){
    int idx = RANDOM * wordle->wordCount;
     
    wordle->chosenWord = strcpy(malloc(wordle->wordlen), wordle->dicc[idx].word);
    return 1;//TODO que poner en return
    }

//se fija si 1 letra de guess esta en word
int check(int i, int size, char *word, char *guess){
    for (int j = 0; j < size; j++){
        if((guess[i]-word[j]) == 0){
            word[j] -= guess[i];
            return ABS(i-j);
            }
        }
    return -1;
    }

//crea la coloracion de la guess con la palabra guardada en el CDT
int checkWord(wordleADT wordle, char *guess, int *estado){
    int total = 0;

    int size = wordle->wordlen-1;

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

int cross(wordleADT wordle, int idx1, int idx2){
    int total = 0;
    int mult = 1;

    int size = wordle->wordlen-1;

    char word1[size+1];
    char word2[size+1];
    
    for(int i = 0; i<size+1; i++){
        word1[i] = wordle->dicc[idx1].word[i];
        word2[i] = wordle->dicc[idx2].word[i];
        }

    int c;
    for (int i = 0; i < size; i++){
        if((c = check(i, size, word2, word1)) < 0){
            total += GREY*mult;
            }
        if(c > 0){
            total += YELLOW*mult;
            }
        if(c == 0) {
            total += GREEN*mult;
            }
        mult *= STATECOUNT;
        }
    return total;
    }

int makeResult(wordleADT wordle){
    wordle->results = malloc(wordle->wordCount*sizeof(int*));
    for (int i = 0; i <wordle->wordCount; i++){
        wordle->results[i] = malloc(wordle->wordCount*sizeof(int));
        }

    for (int i = 0; i <wordle->wordCount; i++){
        for (int j = 0; j < wordle->wordCount; j++){
            wordle->results[i][j] = cross(wordle, i, j);
            }
        }

    return 1;//TODO ver que retorna
    }

infoL *addinfo(infoL *list, double info, char *word){
    if(list == NULL || (list->data.info - info) < EPSILON){
        infoL *aux = malloc(sizeof(infoL));

        aux->tail = list;
        aux->data.info = info;
        aux->data.word = word;

        return aux;
        }
    
    list->tail = addinfo(list->tail, info, word);
    return list;
    }

int *getRes(wordleADT wordle, int idx, int *len){
    int statusCount = pow(STATECOUNT, wordle->wordlen-1);
    int vec[statusCount];

    for(int i = 0; i < statusCount; i++){
        vec[i] = 0;
        }

    *len = 0;

    for(int i = 0; i < wordle->wordCount; i++){
        if(wordle->dicc[idx].status){
            if (vec[wordle->results[idx][i]]++ == 0){
                *len += 1;
                }
            }
        }
    
    int *result = malloc(*len * sizeof(int));
    int count = 0;

    for(int i = 0; count < *len && i < statusCount; i++){
        if(vec[i] != 0){
            result[count++] = vec[i];
            }
        }
    return result;
    }

info *getInfo(wordleADT wordle, int *dim){
    *dim = 0;
    double data;
    char *word;
    int len;
    int *result;
    
    infoL *aux = NULL;
    for(int i = 0; i < wordle->wordCount; i++){
        if(wordle->dicc[i].status){
            data = 0;
            
            result = getRes(wordle, i, &len);

            for(int j = 0; j < len; j++){
                double p = (double)result[j]/wordle->actualCount;
                data -= p*log2(p);
                }

            free(result);

            word = strcpy(malloc(wordle->wordlen), wordle->dicc[i].word);

            aux = addinfo(aux, data, word);
            *dim += 1;
            }
        }

    info *vec = malloc(*dim*sizeof(info));

    infoL *aux2;
    int i = 0;
    while(aux != NULL){
        vec[i] = aux->data;
        aux2 = aux;
        aux = aux->tail;
        free(aux2);
        i++;
        }

    return vec;
    }

//libera memoria
void freeWordle(wordleADT wordle){
    for(int i = 0; i < wordle->wordCount; i++){
        free(wordle->dicc[i].word);
        if (wordle->results != NULL){
            free(wordle->results[i]);
            }
        }
    free(wordle->dicc);
    free(wordle->results);

    free(wordle->chosenWord);

    free(wordle);
    }
