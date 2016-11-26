===========================
Encode:
        executable: ENCODE - take two arguments [source file name] [destination file name]
        source/header file: huffman_encoding.cpp - main(), and other huffman encoding functions
                            huffman.cpp - class: Node 
                            huffman.h - class: Node
The entropy of the original text file: 4.44738
The average path length in the Huffman tree: 4.47009
The entropy of the original text file: 4.59907
The average path length in the Huffman tree: 4.64189
The entropy of the original text file: 4.28772
The average path length in the Huffman tree: 4.32755
===========================
Decode:
        executable: DECODE - take two arguments [source file name] [destination file name]
        source/header file: huffman_decoding.cpp - main(), and other huffman encoding functions
                            huffman.cpp - class: Node 
                            huffman.h - class: Node
RD:decode li$ ./DECODE ./../../small.bin small.txt
RD:decode li$ ./DECODE ./../../medium.bin medium.txt
RD:decode li$ ./DECODE ./../../large.bin large.txt
RD:decode li$ diff small.txt ./../../small.txt
RD:decode li$ diff medium.txt ./../../medium.txt
RD:decode li$ diff large.txt ./../../large.txt
===========================

Steps for decoding:
                    1. read the file. get first 8 bytes (size of header and size of text)
                    2. convert the codes and text into binary string
                    3. construct a huffman tree (I used array, it wastes lots of space but it's easy to implement)
                    4. parse the binary string, which is the compressed text
                    5. write the result to the destination file
