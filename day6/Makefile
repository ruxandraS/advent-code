CC=g++
CFLAGS = -std=c++17 -Wall -Wextra -g
all: orbit
orbit: *.cpp
	$(CC) *.cpp -o orbit $(CFLAGS)
run: orbit
	./orbit
clean:
	rm -rf orbit *.out .DS_Store *.dSYM