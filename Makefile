all: mainC mainH test

mainC: main.o entreeSortieLC.o biblioLC.o
	gcc -o mainC main.o entreeSortieLC.o biblioLC.o

main.o: main.c biblioLC.h entreeSortieLC.h
	gcc -c main.c

entreeSortieLC.o: entreeSortieLC.c entreeSortieLC.h biblioLC.h
	gcc -c entreeSortieLC.c

biblioLC.o: biblioLC.c biblioLC.h
	gcc -c biblioLC.c

mainH: mainH.o entreeSortieLH.o biblioLH.o
	gcc -o mainH mainH.o entreeSortieLH.o biblioLH.o

mainH.o: mainH.c biblioLH.h entreeSortieLH.h
	gcc -c mainH.c

entreeSortieLH.o: entreeSortieLH.c entreeSortieLH.h biblioLH.h
	gcc -c entreeSortieLH.c

biblioLH.o: biblioLH.c biblioLH.h
	gcc -c biblioLH.c

test : biblioLC.h  biblioLH.h entreeSortieLC.h entreeSortieLH.h test.o
	gcc -o test test.o biblioLC.o  biblioLH.o entreeSortieLC.o entreeSortieLH.o

test.o : test.c  biblioLC.h  biblioLH.h entreeSortieLC.h entreeSortieLH.h
	gcc -c test.c

clean:
	rm -f *.o mainC
	rm -f *.o mainC 
	rm -f *.o test
