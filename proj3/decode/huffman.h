#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
using namespace std;

class Node
{
public:
    Node(int ch = -1, int frq = 0, bool isLeaf = 0, Node *left = NULL, Node *right = NULL);
    int ch() { return ch_; }
    int frq() { return frq_; }
    bool isLeaf() { return isLeaf_; }
    Node* left() { return left_; }
    Node* right() { return right_;}
private:
    int ch_;        // the character ascii
    int frq_;       // the frequency
    bool isLeaf_;   // if it is a leaf node, then isLeaf = 1
    Node *left_;    // left child
    Node *right_;   // right child
};

#endif
