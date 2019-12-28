CC = gcc
CFLAGS = -Wall -pedantic -g 
obj = main.o inventory.o stats.o champs.o

a.out: $(obj)
	$(CC) $(CFLAGS) $(obj) -o a.out
main.o: champs.h inventory.h stats.h
champs.o: champs.h stats.h
inventory.o: inventory.h stats.h

.PHONY: clean
clean:
	-rm $(obj) *~
