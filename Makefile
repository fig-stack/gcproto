CC=gcc
CFLAGS=-Wall -Wextra -g -O0
OBJS=garbage.o

garbage: $(OBJS)
			gcc -o $@ $^ 

