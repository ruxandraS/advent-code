CC=g++
CFLAGS = -Wall -Wextra -g -std=c++17
all: test
test: *.cpp
	$(CC) *.cpp -o test $(CFLAGS)
run: test
	./test
clean:
	rm -f test