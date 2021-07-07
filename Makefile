# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall #-g
 
# ****************************************************
# Targets needed to bring the executable up to date
all: main

main: main.o Router.o Terminales.o Cola.o Algoritmos.o Files.o Admin.o
	$(CC) $(CFLAGS) -o main main.o Router.o Terminales.o Cola.o Algoritmos.o Files.o Admin.o

main.o: main.cpp global.h Router.h Terminales.h Cola.h Algoritmos.h Files.h Admin.h
	$(CC) $(CFLAGS) -c main.cpp

Router.o: Router.cpp global.h Cola.h
	$(CC) $(CFLAGS) -c Router.cpp

Terminales.o: Terminales.cpp global.h
	$(CC) $(CFLAGS) -c Terminales.cpp

Cola.o: Cola.cpp global.h
	$(CC) $(CFLAGS) -c Cola.cpp

Algoritmos.o: Algoritmos.cpp global.h
	$(CC) $(CFLAGS) -c Algoritmos.cpp

Files.o: Files.cpp
	$(CC) $(CFLAGS) -c Files.cpp

Admin.o: Admin.cpp  Algoritmos.h Terminales.h
	$(CC) $(CFLAGS) -c Admin.cpp

clean:
	rm *.o main


# ****************************************************
 
#main: main.o Point.o Square.o
#    $(CC) $(CFLAGS) -o main main.o Point.o Square.o
 
# The main.o target can be written more simply
 
#main.o: main.cpp Point.h Square.h
#    $(CC) $(CFLAGS) -c main.cpp
 
#Point.o: Point.h
 
#Square.o: Square.h Point.h
