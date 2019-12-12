CC=g++
CFLAGS = -std=c++17 -Wall -Wextra -g
all: spaceimg
spaceimg: *.cpp
	$(CC) *.cpp -o spaceimg $(CFLAGS)
run: spaceimg
	./spaceimg
clean:
	rm -rf spaceimg *.out .DS_Store *.dSYM *.pbm