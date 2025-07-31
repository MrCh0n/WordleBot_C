COMPILER        = gcc

FLAGS           = -std=c99 -pedantic -Wall
MEM_FLAGS       = -fsanitize=address -g

OBJS_ADT        = WordleADT.o
OBJS_WORDLE     = $(OBJS_ADT) wordle.o
OBJS_BOT        = $(OBJS_ADT) bot.o

BINARY_WORDLE   = wordle
BINARY_BOT      = bot

OBJS            = $(OBJS_ADT) wordle.o bot.o
BINARY          = $(BINARY_WORDLE) $(BINARY_BOT)


all: $(BINARY)

debug: FLAGS += $(MEM_FLAGS)
debug: all

wordle:$(OBJS_WORDLE)
	$(COMPILER) $(FLAGS) $(OBJS_WORDLE) -o $(BINARY_WORDLE) -lm

bot:$(OBJS_BOT)
	$(COMPILER) $(FLAGS) $(OBJS_BOT) -o $(BINARY_BOT) -lm

wordle.o: wordle.c WordleADT.h
	$(COMPILER) $(FLAGS) -c wordle.c

bot.o: WordleADT.h bot.c
	$(COMPILER) $(FLAGS) -c bot.c

WordleADT.o: WordleADT.h WordleADT.c
	$(COMPILER) $(FLAGS) -c WordleADT.c

clear:
	rm $(BINARY)
	rm $(OBJS)

