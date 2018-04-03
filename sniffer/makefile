daemon: main.o sniff.o avltree.o
	gcc main.o sniff.o avltree.o -o daemon -lpcap -lrt

main.o: main.c sniff.h
	gcc -c main.c

sniff.o: sniff.c sniff.h avltree.h
	gcc -c  sniff.c

avltree.o: avltree.c avltree.h
	gcc -c avltree.c

clean:
	\rm *.o daemon
