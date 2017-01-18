#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include "node.h"
using namespace std;

class Trie
{
public:
    Trie() { root = new (nothrow) Node(); }
    ~Trie();
    void addWord(string s);
    int searchWord(string s);
    void deleteWord(string s);
private:
    Node * root;
};

#endif

