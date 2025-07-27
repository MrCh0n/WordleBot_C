COMPILER        = gcc

FLAGS           = -std=c99 -pedantic
MEM_FLAGS       = $(FLAGS) -fsanitize=address -g

OBJS            = WordleADT.o wordle.o

BINARY          = wordle

all.o: $(OBJS)
	$(COMPILER) $(MEM_FLAGS) $(OBJS) -o $(BINARY)

wordle.o: wordle.c WordleADT.h
	$(COMPILER) $(FLAGS) -c wordle.c

WordleADT.o: WordleADT.h WordleADT.c
	$(COMPILER) $(FLAGS) -c WordleADT.c

clear:
	rm $(BINARY)
	rm $(OBJS)

