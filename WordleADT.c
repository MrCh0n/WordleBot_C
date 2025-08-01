#include "WordleADT.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

//TODO funcion de eliminar palabras incogruentes

//define FILENAME "prueba.txt"
#define SOLUTIONS "possible_solutions.txt"
#define TOTALWORDS "words.txt"
#define BITS 8

#define BLOCK 64

#define LETTERS ('z'-'a'+1)
#define RANDOM (double)(rand()/((double)RAND_MAX+1))
#define IDX(c) (c[0]-'a')

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
    size_t wordCount;
    size_t actualCount;
    
    char **dicc_total[LETTERS];
    size_t amount_total[LETTERS];

    size_t wordlen;

    int **results;

    char *chosenWord;
    }CDT;


int addFile(wordleADT wordle, char *solutions, char *total_words);

int choseWord(wordleADT wordle);

wordleADT newWordle(){
    srand(time(NULL));

    wordleADT aux = calloc(1,sizeof(CDT));
    
    addFile(aux, SOLUTIONS, TOTALWORDS);

    choseWord(aux);

    return aux;
    }

int sizeWord(wordleADT wordle){
    return wordle->wordlen - 1;
    }

char *getWord(wordleADT wordle){
    return strcpy(malloc(wordle->wordlen), wordle->chosenWord);
    }

//parsea filename para conseguir las palabras
int addFile(wordleADT wordle, char *solutions, char *total_words){
    FILE *file = fopen(solutions, "r");//TODO cheackear fopen
    char word[BITS];

    int reserved = 0;

    char *p;

    if((p = fgets(word, BITS, file)) == NULL){
        //TODO esta vacio
        }

    wordle->wordlen = strlen(word);

    while(p != NULL){
        word[wordle->wordlen - 1] = '\0';
        if(wordle->wordCount >= reserved){
            reserved += BLOCK;
            wordle->dicc = realloc(wordle->dicc, sizeof(words)*reserved);
            }

        wordle->dicc[wordle->wordCount].word = strcpy(malloc(wordle->wordlen), word);
        wordle->dicc[wordle->wordCount].status = 1;
        wordle->wordCount += 1;

        p = fgets(word, BITS, file);
        }

    wordle->dicc = realloc(wordle->dicc, wordle->wordCount*sizeof(words));

    wordle->actualCount = wordle->wordCount;

    fclose(file);

    file = fopen(total_words, "r");

    if((p = fgets(word, BITS, file)) == NULL){
        //TODO esta vacio
        }

    while(p != NULL){
        word[wordle->wordlen - 1] = '\0';
        int idx = IDX(word);

        if(wordle->amount_total[idx] == 0){
            reserved = 0;
            }


        if(wordle->amount_total[idx] >= reserved){
            reserved += BLOCK;
            wordle->dicc_total[idx] = realloc(wordle->dicc_total[idx], sizeof(char*)*reserved);
            }
        
        wordle->dicc_total[idx][wordle->amount_total[idx]] = strcpy(malloc(wordle->wordlen), word);
        wordle->amount_total[idx] += 1;

        p = fgets(word, BITS, file);
        }

    for(int i = 0; i<LETTERS; i++){
        wordle->dicc_total[i] = realloc(wordle->dicc_total[i], sizeof(char*)*wordle->amount_total[i]);
        }

    fclose(file);
    return 1;
    }

//elije una palabra del vector dicc y la guarda
int choseWord(wordleADT wordle){
    int idx = RANDOM * wordle->wordCount;
     
    wordle->chosenWord = strcpy(malloc(wordle->wordlen), wordle->dicc[idx].word);
    return 1;//TODO que poner en return
    }

//se fija si guess esta en las totales
int check_total(wordleADT wordle, char *guess){
    int idx = IDX(guess);

    char **vec;
    vec = wordle->dicc_total[idx];

    int low = 0;
    int high = wordle->amount_total[idx] - 1;

    while(low <= high){
        int mid = (low + high)/2;
        int c;

        if((c = strcmp(guess, vec[mid])) == 0){
            return 1;
            }
        if(c < 0){
            high = mid - 1;
            }
        if(c > 0){
            low = mid + 1;
            }
        }
    return 0;
    }

//se fija si 1 letra de guess esta en word
int check(int i, int size, char *word, char *guess){
    for (int j = 0; j < size; j++){
        if((guess[i]-word[j]) == 0 && !(guess[i] == guess[j] && i != j)){
            word[j] -= guess[i];
            if(i == j){
                return GREEN;
                }
            return YELLOW;
            }
        }
    return GREY;
    }

//crea la coloracion de la guess con la palabra guardada en el CDT
int checkWord(wordleADT wordle, char *guess, int *estado){
    if(!check_total(wordle, guess)){
        return 0;
        }

    int total = 0;

    int size = wordle->wordlen-1;

    char word[size];
    for(int i = 0; i<size; i++){
        word[i] = wordle->chosenWord[i];
        }

    int c;
    for (int i = 0; i < size; i++){
        c = check(i, size, word, guess);
        estado[i] = c;
        total += c;
        }

    if(total == size*GREEN){
        return 1;
        }

    return -1;
    }

int cross(wordleADT wordle, int idx1, int idx2, int mult[]){
    int total = 0;

    int size = wordle->wordlen-1;

    char word1[size+1];
    char word2[size+1];
    
    for(int i = 0; i<size+1; i++){
        word1[i] = wordle->dicc[idx1].word[i];
        word2[i] = wordle->dicc[idx2].word[i];
        }
    int c;
    for (int i = 0; i < size; i++){
        c = check(i, size, word2, word1);
        total += c*mult[size-i-1];
        }
    return total;
    }

int makeResult(wordleADT wordle){
    wordle->results = malloc(wordle->wordCount*sizeof(int*));

    int mult[wordle->wordlen-1];
    mult[0] = 1;

    for(int i = 1; i < wordle->wordlen-1; i++){
        mult[i] = mult[i-1]*STATECOUNT;
        }

    for (int i = 0; i <wordle->wordCount; i++){
        wordle->results[i] = malloc(wordle->wordCount*sizeof(int));
        for (int j = 0; j < wordle->wordCount; j++){
            wordle->results[i][j] = cross(wordle, i, j, mult);
            }
        }

    return 1;//TODO ver que retorna
    }

infoL *addinfo(infoL *list, double info, char *word){
    if(list == NULL || (list->data.info - info) < 0){
        infoL *aux = malloc(sizeof(infoL));

        aux->tail = list;
        aux->data.info = info;
        aux->data.word = word;

        return aux;
        }
    
    list->tail = addinfo(list->tail, info, word);
    return list;
    }

double getRes(wordleADT wordle, int idx, int *len, int statusCount){
    int vec[statusCount];
    for(int i = 0; i < statusCount; i++){
        vec[i] = 0;
        }

    *len = 0;

    for(int i = 0; i < wordle->wordCount; i++){
        if(wordle->dicc[i].status){
            int c = wordle->results[idx][i];
            if (vec[c] == 0){
                *len += 1;
                }
            vec[c] += 1;
            }
        }
    
    double data = 0;
    int count = 0;

    for(int i = 0; count < *len && i < statusCount; i++){
        if(vec[i] != 0){
            double p = (double)vec[i]/wordle->actualCount;
            data -= p*log2(p);
            count++;
            }
        }

    return data;
    }

info *getInfo(wordleADT wordle, int *dim){
    *dim = 0;
    double data;
    char *word;
    int len;

    int statusCount = pow(STATECOUNT, wordle->wordlen-1);
    
    infoL *aux = NULL;
    for(int i = 0; i < wordle->wordCount; i++){
        if(wordle->dicc[i].status){
            data = getRes(wordle, i, &len, statusCount);

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

    for(int i = 0; i<LETTERS; i++){
        for(int j = 0; j < wordle->amount_total[i]; j++){
            free(wordle->dicc_total[i][j]);
            }
        free(wordle->dicc_total[i]);
        }

    free(wordle->chosenWord);

    free(wordle);
    }
