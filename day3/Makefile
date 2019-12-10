CC=g++
CFLAGS = -Wall -Wextra -g -std=c++17
all: wires
wires: *.cpp
	$(CC) *.cpp -o wires $(CFLAGS)
run: wires
	./wires
clean:
	rm -f wires