#include "huffman.h"
#include <queue>

// constructor
Node::Node(int ch, int frq, bool isLeaf, Node* left, Node* right)
{
    ch_ = ch;
    frq_ = frq;
    isLeaf_ = isLeaf;
    left_ = left;
    right_ = right;
}





