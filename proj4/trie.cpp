#include "trie.h"
#include "node.h"

Trie::~Trie()
{
    Node * cursor = root;
    while(cursor->children().size())
    {
        free(cursor);
    }
}

void Trie::addWord(string s)
{
    Node * current = root;

    if(s.length() == 0)         // empty word
    {
        current->setIsLeaf();
        return;
    }
    for(int i = 0; i < s.length(); i++)     // adding each character into trie
    {
        Node * child = current->getChild(s[i]);
        if(child)                           // exist s[i]!
            current = child;
        else
        {
            Node * tmp = new (nothrow) Node();
            tmp->setCh(s[i]);
            current->appendChild(tmp);      // add s[i]
            current = tmp;
        }
        if(i + 1 == s.length())
            current->setIsLeaf();           // a leaf node
    }
}

int Trie::searchWord(string s)
{
    Node * current = root;
    while(current)
    {
        for(int i = 0; i < s.length(); i++)     // go to the end of the word
        {
            Node * tmp = current->getChild(s[i]);
            if(!tmp)
                return 0;
            current = tmp;
        }
        if(current->isLeaf())                   // if the end of the word is marked as a leaf in trie, then it is a legit word
            return s.length();                  // specifying the length of the word that ends here
        else
            return 0;
    }
    return 0;
}

