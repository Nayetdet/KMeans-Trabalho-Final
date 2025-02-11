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

all: bin/main bin/dice bin/histogram bin/sse

bin:
	mkdir bin

obj:
ifeq ($(OS),Windows_NT)
	mkdir obj obj\src obj\tests obj\tests\src
else
	mkdir obj obj/src obj/tests obj/tests/src
endif

clean:
ifeq ($(OS),Windows_NT)
	rmdir /s /q bin obj
else
	rm -rf bin obj
endif

# Main:

bin/main: obj/main.o obj/src/pgm.o obj/src/kmeans.o | bin
	gcc -o $@ $^ -lm -O3

obj/main.o: main.c | obj
	gcc -o $@ -c $< -Iinclude -O3

obj/src/pgm.o: src/pgm.c | obj
	gcc -o $@ -c $< -Iinclude -O3

obj/src/kmeans.o: src/kmeans.c | obj
	gcc -o $@ -c $< -Iinclude -O3

# Dice:

bin/dice: obj/tests/dice.o obj/tests/src/dice.o obj/tests/src/utils.o obj/src/pgm.o | bin
	gcc -o $@ $^ -lm -O3

obj/tests/dice.o: tests/dice.c | obj
	gcc -o $@ -c $< -Iinclude -Itests/include -O3

obj/tests/src/dice.o: tests/src/dice.c | obj
	gcc -o $@ -c $< -Iinclude -Itests/include -O3

obj/tests/src/utils.o: tests/src/utils.c | obj
	gcc -o $@ -c $< -Itests/include -O3

# Histograma:

bin/histogram: obj/tests/histogram.o obj/tests/src/histogram.o obj/src/pgm.o | bin
	gcc -o $@ $^ -O3

obj/tests/histogram.o: tests/histogram.c | obj
	gcc -o $@ -c $< -Iinclude -Itests/include -O3

obj/tests/src/histogram.o: tests/src/histogram.c | obj
	gcc -o $@ -c $< -Iinclude -Itests/include -O3

# SSE:

bin/sse: obj/tests/sse.o obj/tests/src/sse.o obj/src/pgm.o obj/src/kmeans.o | bin
	gcc -o $@ $^ -lm -O3

obj/tests/sse.o: tests/sse.c | obj
	gcc -o $@ -c $< -Iinclude -Itests/include -O3

obj/tests/src/sse.o: tests/src/sse.c | obj
	gcc -o $@ -c $< -Iinclude -Itests/include -O3
