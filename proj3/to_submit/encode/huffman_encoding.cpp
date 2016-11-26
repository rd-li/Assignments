#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <math.h>
#include "huffman.h"
using namespace std;

// compare function for the priority queue
struct compare
{
    bool operator()(Node* lhs, Node* rhs)
    {
        return ((*lhs).frq() > (*rhs).frq());
    }
};
void huffman_func(int frq[]);
void generateCode(Node * n, string code);
void writeFile(char * filename, string text, const unsigned int * size);
void writeBit(ofstream &outfile, int bit);
void FlushBits(ofstream &outfile);
void calcEntropyLength(int frq[], int size);

// global variables
int currentBit = 7;
unsigned char bitBuffer = 0;
string codeList[256];

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cerr << "usage: " << argv[0] << " [source filename] [output filename]\n";
        return 0;
    }
    // open the file
    ifstream inFile(argv[1], ios::in);      // fstream for file
    if(inFile.fail())
    {
        cerr << "Could not open file\n";
        return 0;
    }
    // read in the content to string textfile
    // got the following single line from this website http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    string textfile((istreambuf_iterator<char>(inFile)), (istreambuf_iterator<char>()));
    unsigned int n = textfile.length();     // size of textfile
    int occurrence[256] = {};               // frequency list
    
    // go through each character in the text and count the frequency
    for(int i = 0; i < n; i++)
        occurrence[(int)((unsigned char)textfile[i])]++;
    // initialize all the code with null terminator
    for(int i = 0; i < 256; i++)
        codeList[i] = '\0';
    
    // do the huffman compression
    huffman_func(occurrence);    
    // close the file
    inFile.close();

    // write the compressed file using the code, calculate entropy, and calculate average path length
    writeFile(argv[2], textfile, &n);
    calcEntropyLength(occurrence, n);

    return 0;
}

// huffman function to generate code for each char
void huffman_func(int frq[])
{
    int n = 256;        // number of characters, no matter freq = 0 or not
    Node *left;         // left node
    Node *right;        // right node
    Node *parent;       // parent node

    // use priority queue, key is the frequency
    priority_queue<Node*, vector<Node*>, compare> huffTree;
    for(unsigned int i = 0; i < n; i++)
        if(frq[i] != 0)
            huffTree.push(new (nothrow) Node(i, frq[i], 1, NULL, NULL));        // flag isLeaf == 1
    
    while(huffTree.size() != 1)
    {
        left = huffTree.top();
        huffTree.pop();
        right = huffTree.top();
        huffTree.pop();

        parent = new (nothrow) Node(-1, left->frq() + right->frq(), 0, left, right);        // internal nodes for construncting the path
        huffTree.push(parent);
    }
    // generate code according to the tree
    generateCode(huffTree.top(), "");
}

// generate code
void generateCode(Node * n, string code)
{
    // hit null, then return (return to nodes that isLeaf == 1)
    if(n == NULL)
        return;
    // leaf node, start generating code
    if(n->isLeaf() == 1)
        codeList[n->ch()] = code + '\0';
    // call left child and right child
    generateCode(n->left(), code + '0');
    generateCode(n->right(), code + '1');
}

// write the result to the file
void writeFile(char * filename, string text, const unsigned int * size)
{
    ofstream outFile(filename, ios::out | ios::binary);
    unsigned int headerSize = 8;    // first four byte
    int tmpLengthHolder = 0;        // tmp
    unsigned short tmpCode = 0;     // tmp
    unsigned int contentSize = *size;
    // count how many bytes needed for the header (how many characters are there in the text)
    for(int i = 0; i < 256; i++)
        if(codeList[i][0] != '\0')
            headerSize += 4;
    // write the header size and text size
    outFile.write((char *)(&headerSize), sizeof(unsigned int) * 1);
    outFile.write((char *)(&contentSize), sizeof(unsigned int) * 1);
    // write the code in the header
    for(int i = 0; i < 256; i++)
    {
        tmpLengthHolder = codeList[i].length() - 1;
        if(tmpLengthHolder)
        {
            tmpCode = stoi(codeList[i], nullptr, 2);
            outFile.write((char *)(&i), sizeof(unsigned char) * 1);
            outFile.write((char *)(&tmpLengthHolder), sizeof(unsigned char) * 1);
            outFile.write((char *)(&tmpCode), sizeof(unsigned short) * 1);
        }
    }
    // compress the text according to our code
    string tmp;                     // tmp
    for(int i = 0; i < *size; i++)
    {
        tmp = codeList[(int)((unsigned char)text[i])];
        for(int j = 0; j < tmp.length() - 1; j++)
        {
            if(tmp[j] == '1')
                writeBit(outFile, 1);
            else if (tmp[j] == '0')
                writeBit(outFile, 0);
            else
                cout << "wrong...\n";        
        }
    }
    // flush the bits (if any remaining)
    FlushBits(outFile);
    outFile.close();
}

// write bits
void writeBit(ofstream &outfile, int bit)
{
    if(bit)
        bitBuffer |= (1<<currentBit);
    currentBit --;
    if(currentBit == -1)
    {
        outfile.write((char *)(&bitBuffer), 1);
        currentBit = 7;
        bitBuffer = 0;
    }
}

void FlushBits(ofstream &outfile)
{
    while(currentBit != 7)
        writeBit(outfile, 0);
}

// calculate the entropy and average path length of the file
void calcEntropyLength(int frq[], int size)
{
    float entropy = 0.0;
    float p = 0.0;
    float totalLen = 0;
    for(int i = 0; i < 256; i++)
    {
        if(frq[i] != 0)
        {
            p = frq[i] / (float)size;
            entropy += ((-1) * p * log2(p));
            totalLen += (p * (codeList[i].length() - 1));
        }
    }
    cout << "The entropy of the original text file: " << entropy << endl;
    cout << "The average path length in the Huffman tree: " << totalLen << endl;
}


