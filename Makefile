objs = main.c list.o
out = mhkonbu
opt = 
CC = gcc $(opt)
libs =
headers = defines.h list.h
ARG = test.md

$(out): $(objs)
	$(CC) $(objs) -o $(out) $(libs)

list.o: list.c list.h
	$(CC) -c list.c -o list.o $(libs)

run:
	./$(out) $(ARG)

.PHONY: clean
clean:
	rm $(out)
	rm *.o

.PHONY: all
all:
	make $(out)
	make run

