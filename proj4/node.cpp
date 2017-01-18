#include "node.h"

Node* Node::getChild(char ch)
{
    for(int i = 0; i < children_.size(); i++)
    {
        Node * tmp = children_.at(i);
        if(tmp->ch() == ch)
            return tmp;
    }
    return NULL;
}
