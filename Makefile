.SUFFIXES: .cpp

CC = g++
CFLAGS = -g -I/usr/local/include -DPRINT -std=c++11
LDIR =
LIBS =

OBJ = Contact.o InsertionSort.o QuickSort.o MergeSort.o ContactList.o main.o

PEX1: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDIR) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) -c $?

clean:
	rm -f PEX1 $(OBJ) $(OBJ2)
