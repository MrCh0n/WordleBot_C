#ifndef wordle_ADT_h
#define wordle_ADT_h

typedef enum STATES {GREY = 0, YELLOW, GREEN, STATECOUNT} STATES;

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
// devuele 0 si hay error 
// -1 si no es la palabra
// 1 si es la palabra
// o el largo de estado en otro caso
// liberar estado despues
int checkWord(wordleADT worlde, char *guess, int *estado);

//FUNCIONES PARA EL BOT

//crea los datos necesarios para usar el bot
int makeResult(wordleADT wordle);

void freeWordle(wordleADT wordle);

#endif //wordle_ADT_h
