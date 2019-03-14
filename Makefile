objs = main.c
out = mhkonbu
opt = 
CC = gcc $(opt)
libs =
headers = defines.h
ARG = test.md

$(out): $(objs)
	$(CC) $(objs) -o $(out) $(libs)

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

