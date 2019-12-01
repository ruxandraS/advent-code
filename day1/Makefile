CC=g++
CFLAGS = -Wall -Wextra -g
all: rocketeq
rocket: *.cpp
	$(CC) *.cpp -o rocketeq $(CFLAGS)
run: rocketeq
	./rocketeq
clean:
	rm -f rocketeq