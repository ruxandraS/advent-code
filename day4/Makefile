CC=g++
CFLAGS = -std=c++11 -Wall -Wextra -g
all: container
container: *.cpp
	$(CC) *.cpp -o container $(CFLAGS)
run: container
	./container
clean:
	rm -rf container *.out .DS_Store *.dSYM