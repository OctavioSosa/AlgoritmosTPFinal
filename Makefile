# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall #-g
 
# ****************************************************
# Targets needed to bring the executable up to date
all: main

main: main.o Router.o Terminales.o Cola.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main.cpp Router.h Terminales.h Cola.h
	$(CC) $(CFLAGS) -c main.cpp

Router.o: Router.cpp
	$(CC) $(CFLAGS) -c Router.cpp

Terminales.o: Terminales.cpp
	$(CC) $(CFLAGS) -c Terminales.cpp

Cola.o: Cola.cpp
	$(CC) $(CFLAGS) -c Cola.cpp

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