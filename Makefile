all: clean main dice histogram

main:
	gcc main.c src/*.c -o main -Iinclude -lm -O3

dice:
	gcc tests/dice.c src/*.c tests/src/*.c -o dice -Iinclude -Itests/include -O3

histogram:
	gcc tests/histogram.c src/*.c tests/src/*.c -o histogram -Iinclude -Itests/include -O3

clean:
	rm -f main dice histogram
