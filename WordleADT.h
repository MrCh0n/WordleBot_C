#ifndef wordle_ADT_h
#define wordle_ADT_h

typedef enum STATES {GREY = 0, YELLOW, GREEN, STATECOUNT} STATE;

typedef struct wordleCDT * wordleADT;

//crea un nuevo wordle con las palabras en file
wordleADT newWordle();

//carga word a las posibles palabras
//TODO retorna ??
int addWords(wordleADT wordle, char *word);

//elije una palabra de las posibles
//TODO devuelve ?? si hay error o no
int choseWord(wordleADT wordle);

//devuele 0 si hay error 
//-1 si es la palabra
//o el largo de estado en otro caso
int checkWord(wordleADT worlde, char *guess, int estado[]);


#endif //wordle_ADT_h
