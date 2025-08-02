#ifndef wordle_ADT_h
#define wordle_ADT_h

typedef enum STATES {GREY = 0, YELLOW, GREEN, STATECOUNT} STATES;

//devolucion de getInfo
typedef struct info{
    char *word;
    double info;
    }info;

typedef struct wordleCDT * wordleADT;

//FUNCIONES GENERALES QUE SE PUEDEN USAR PARA JUGAR

// crea un nuevo wordle y elije la palabra a encontrar
wordleADT newWordle();

// retorna el tamano de palabra sin '\0'
int sizeWord(wordleADT wordle);

//retorna la palabra en la quiz, liberar
char *getWord(wordleADT wordle);

// carga word a las posibles palabras
//TODO retorna ??

//int addWords(wordleADT wordle, char *word);

// elije una palabra nueva de las posibles
//TODO devuelve ?? si hay error o no
int choseWord(wordleADT wordle);

// devuelve en estado los valores de guess
// -1 si no es la palabra
// 1 si es la palabra
// 0 si la palabra no es valida
int checkWord(wordleADT worlde, char *guess, int *estado);

//FUNCIONES PARA EL BOT

//crea los datos necesarios para usar el bot
int makeResult(wordleADT wordle);

//devueve un vector ordenado por info y la cantidad de elementos en dim
//devuelve la info ganada por la palabra que se elijio
//liberar las words
info *getInfo(wordleADT worlde, int *dim, double *infoGained);

void freeWordle(wordleADT wordle);

#endif //wordle_ADT_h
