CC=g++
CFLAGS = -std=c++17 -Wall -Wextra -g
all: amplifier
amplifier: *.cpp
	$(CC) *.cpp -o amplifier $(CFLAGS)
run: amplifier
	./amplifier
clean:
	rm -rf amplifier *.out .DS_Store *.dSYM