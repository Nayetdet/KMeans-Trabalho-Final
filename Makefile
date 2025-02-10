# ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
# * Aluno: João Pedro Moreira Campos de Lima              *
# * Matrícula: 20241045050391                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
# * Aluno: Isaac da Cunha Cavalcanti Duarte               *
# * Matrícula: 20241045050375                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
# * Aluno: Josué Rodrigues Avelino                        *
# * Matrícula: 20241045050219                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
# * Aluno: Orleoncio Maciel                               *
# * Matrícula: 20181045050165                             *
# * Avaliação 04: Trabalho Final                          *
# * 04.505.23 − 2024.2 − Prof. Daniel Ferreira            *
# * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
# ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗

all: main dice histogram sse

main:
	gcc main.c src/*.c -o main -Iinclude -lm -O3

dice:
	gcc tests/dice.c src/*.c tests/src/*.c -o dice -Iinclude -Itests/include -lm -O3

histogram:
	gcc tests/histogram.c src/*.c tests/src/*.c -o histogram -Iinclude -Itests/include -O3

sse:
	gcc tests/sse.c src/*.c tests/src/*.c -o sse -Iinclude -Itests/include -O3

clean:
	rm -f main dice histogram
