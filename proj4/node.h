#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    Node() { ch_ = ' '; isLeaf_ = false; }
    ~Node() {}
    char ch() { return ch_; }
    void setCh(char ch) { ch_ = ch; }
    bool isLeaf() { return isLeaf_; }
    void setIsLeaf() { isLeaf_ = true; }
    Node * getChild(char ch);
    void appendChild(Node * child) { children_.push_back(child); }
    vector<Node*> children() {return children_; }

private:
    char ch_;
    bool isLeaf_;
    vector<Node*> children_;
};

#endif

