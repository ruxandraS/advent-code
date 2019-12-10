CC=g++
CFLAGS = -Wall -Wextra -g -std=c++17
all: alarm
alarm: *.cpp
	$(CC) *.cpp -o alarm $(CFLAGS)
run: alarm
	./alarm
clean:
	rm -f alarm