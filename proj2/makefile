.SUFFIXES: .cpp

CC = g++
CFLAGS = -g -I/usr/local/include -DPRINT -std=c++11
LDIR =
LIBS =

OBJ = wavCode.o fftCode.o main.o

PEX2: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDIR) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) -c $?

clean:
	rm -f PEX1 $(OBJ) $(OBJ2)
