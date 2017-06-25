.PHONY: all clean

all: calcFrequency

calcFrequency: build/main.o build/process.o src/process.h
	gcc -Wall build/main.o build/process.o -o calcFrequency

build/main.o: src/main.c src/process.h
	mkdir build -p
	gcc -I scr -Wall -c src/main.c -o build/main.o

build/process.o: src/process.c src/process.h
	mkdir build -p
	gcc -Wall -c src/process.c -o build/process.o

clean:
	rm -f build/* build/* calc*
