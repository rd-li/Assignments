.SUFFIXES: .cpp

CC = g++
CFLAGS = -g -I/usr/local/include -DPRINT -std=c++11
LDIR =
LIBS =

OBJ = huffman.o huffman_encoding.o

ENCODE: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDIR) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) -c $?

clean:
	rm -f PEX3 $(OBJ) $(OBJ2)
