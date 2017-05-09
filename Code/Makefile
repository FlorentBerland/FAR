CFLAGS=-lpthread -D_REENTRANT -lm

all: main.o liste.o tablach.o driver_cptr.o driver_ctrl.o gopigo.o rectangle.o headers/*.h
	gcc -I headers -o main *.o $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

liste.o: code/liste.c
	gcc -c code/liste.c $(CFLAGS)

tablach.o: code/tablach.c
	gcc -c code/tablach.c $(CFLAGS)

rectangle.o: code/rectangle.c
	gcc -c code/rectangle.c $(CFLAGS)

driver_cptr.o: code/driver_cptr.c
	gcc -c code/driver_cptr.c $(CFLAGS)

driver_ctrl.o: code/driver_ctrl.c
	gcc -c code/driver_ctrl.c $(CFLAGS)

gopigo.o: code/gopigo.c
	gcc -c code/gopigo.c $(CFLAGS)

clean:
	rm -rf *.o;
