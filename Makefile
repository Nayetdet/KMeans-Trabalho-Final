# *********************************************************
# * Aluno: João Pedro Moreira Campos de Lima              *
# * Matrícula: 20241045050391                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# *********************************************************
# * Aluno: Isaac da Cunha Cavalcanti Duarte               *
# * Matrícula: 20241045050375                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# *********************************************************
# * Aluno: Josué Rodrigues Avelino                        *
# * Matrícula: 20241045050219                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# *********************************************************
# * Aluno: Orleoncio Maciel                               *
# * Matrícula: 20181045050165                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# *********************************************************

ifeq ($(OS),Windows_NT)
  	MKDIR = mkdir
  	RM = rmdir /s /q
  	OBJDIRS = obj\src obj\tests\src
else
  	MKDIR = mkdir -p
	RM = rm -rf
  	OBJDIRS = obj/src obj/tests/src
endif

all: bin/main bin/dice bin/histogram bin/sse

bin:
	$(MKDIR) bin

obj:
	$(MKDIR) $(OBJDIRS)

bin/main: obj/main.o obj/src/pgm.o obj/src/kmeans.o | bin
	gcc -o $@ $^ -lm -O3

bin/dice: obj/tests/dice.o obj/tests/src/dice.o obj/tests/src/utils.o obj/src/pgm.o | bin
	gcc -o $@ $^ -lm -O3

bin/histogram: obj/tests/histogram.o obj/tests/src/histogram.o obj/src/pgm.o | bin
	gcc -o $@ $^ -O3

bin/sse: obj/tests/sse.o obj/tests/src/sse.o obj/src/pgm.o obj/src/kmeans.o | bin
	gcc -o $@ $^ -lm -O3

obj/%.o: %.c | obj
	gcc -o $@ -c $< -Iinclude -Itests/include -O3

clean:
	$(RM) bin obj
