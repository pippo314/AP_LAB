CC = gcc
CFLAGS = -Wall -pedantic -g 
obj = main.o stat.o inv.o invArray.o equipArray.o Pg.o pgList.o

a.out: $(obj)
	$(CC) $(CFLAGS) $(obj) -o a.out
main.o: pgList.h Pg.h invArray.h
pgList.o: Pg.h
Pg.o: Pg.h stat.h equipArray.h invArray.h inv.h stat.h
equipArray.o: invArray.h
invArray.o: inv.h
inv.o: stat.h

.PHONY: clean
clean:
	-rm $(obj) *~
