#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <math.h>
#include <cstdlib>
#include "huffman.h"
using namespace std;

string readin(char* filename, unsigned int* c_size);
string convert_to_code(unsigned short num, unsigned int length);
string process_content(unsigned char c);
void decode_func(string content, unsigned int size, char* filename);
int get_index(string code);
string codeList[256];

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cerr << "usage: " << argv[0] << " [source filename] [output filename]\n";
        return 0;
    }
    // initialize all the code with null terminator
    for(int i = 0; i < 256; i++)
        codeList[i] = '\0';
    // get the content from the binary file, and the size of it
    unsigned int * c_size = (unsigned int *) malloc(sizeof(unsigned int) * 1);  
    string content = readin(argv[1], c_size);
    // decode the binary file
    decode_func(content, (unsigned int)(*c_size), argv[2]);
}

string readin(char* filename, unsigned int* c_size)
{
    // open the file
    ifstream inFile(filename, ios::in | ios::binary);      // fstream for file
    if(inFile.fail())
    {
        cerr << "Could not open file\n";
        exit(0);
    }
    // read in the header size and the text size
    unsigned int * h_size = (unsigned int *) malloc(sizeof(unsigned int) * 1);  
    inFile.read((char *)h_size, sizeof(unsigned int) * 1);
    inFile.read((char *)c_size, sizeof(unsigned int) * 1);
    
    // read in the header
    unsigned int num_of_dict = ((*h_size) - 8) / 4;
    unsigned char * code_ch = (unsigned char *) malloc(sizeof(unsigned char) * 1);
    unsigned char * code_length = (unsigned char *) malloc(sizeof(unsigned char) * 1);
    unsigned short * code = (unsigned short *) malloc(sizeof(unsigned short) * 1);
    unsigned int tmp_length_holder = 0;
    unsigned short tmp_code = 0;
    for(unsigned int i = 0; i < num_of_dict; i++)
    {
        inFile.read((char *)code_ch, sizeof(unsigned char) * 1);
        inFile.read((char *)code_length, sizeof(unsigned char) * 1);
        inFile.read((char *)code, sizeof(unsigned short) * 1);
        tmp_length_holder = (unsigned int) *code_length;
        tmp_code = (((unsigned short) *code) & ((1 << tmp_length_holder) - 1));
        codeList[(unsigned int)((unsigned char) *code_ch)] = convert_to_code(tmp_code, tmp_length_holder);
    }

    // read in the content, parse it, and convert it to a string consists of 0 and 1
    string tmp_content((istreambuf_iterator<char>(inFile)), (istreambuf_iterator<char>()));
    string content = "";
    for(int i = 0; i < tmp_content.length(); i++)
        content += process_content(tmp_content[i]);
    content += '\0';
    inFile.close();
    return content;
}

string convert_to_code(unsigned short num, unsigned int length)
{
    string code = "";
    int rem = 0;
    while(num > 0)
    {
        rem = num % 2;
        if(rem)
            code = '1' + code;
        else
            code = '0' + code;
        num = (int)(num / 2);
    }
    code += '\0';
    while(code.length() < (length + 1))
        code = '0' + code;
    return code;
}

string process_content(unsigned char c)
{
    unsigned int num = (unsigned int) c;
    string content = "";
    int rem = 0;
    while(num > 0)
    {
        rem = num % 2;
        if(rem)
            content = '1' + content;
        else
            content = '0' + content;
        num = (int)(num / 2);
    }
    while(content.length() < 8)
        content = '0' + content;
    return content;
}

void decode_func(string content, unsigned int size, char* filename)
{
    // calculate the max length of the code for allocate enough space for the huffman tree
    int max_length = 0;
    for(int i = 0; i < 256; i++)
        if(codeList[i][0] != '\0' && codeList[i].length() > max_length)
            max_length = codeList[i].length();
    const int tree_size = (int)pow(2, max_length) + 1;
    // build the huffman tree
    int * huff_tree = new (nothrow) int[tree_size];
    for(int i = 0; i < tree_size; i++)
        huff_tree[i] = -1;
    for(int i = 0; i < 256; i++)
        if(codeList[i][0] != '\0')
            huff_tree[get_index(codeList[i])] = i;
    // parse the content
    unsigned char * result = new (nothrow) unsigned char[size];
    for(int i = 0; i < size; i++)
        result[i] = ' ';
    int index = 1;
    int j = 0;
    for(int i = 0; i < content.length() - 1; i++)
    {
        if(content[i] == '0')
            index *= 2;
        else if(content[i] == '1')
            index = index * 2 + 1;
        //else
            //cout << "Error while decoding [" << i << "]\n";
        if(index > tree_size)
            cout << "Error while decoding [" << i << "]\n";
        if(huff_tree[index] != -1)
        {
            result[j] = (unsigned char) (huff_tree[index]);
            index = 1;
            j++;
        }
    }
    cout << "here\n";
    // write the decoded text into file
    ofstream outFile(filename, ios::out);
    for(int i = 0; i < size; i++)
        outFile.write(reinterpret_cast<char*>(&result[i]), sizeof(unsigned char) * 1);
    outFile.close();
}


int get_index(string code)
{
    int index = 1;
    for(int i = 0; i < (code.length() - 1); i++)
    {
        if(code[i] == '0')
            index *= 2;
        else if(code[i] == '1')
            index = index * 2 + 1;
        else
            cout << "Error\n";
    }
    return index;
}

