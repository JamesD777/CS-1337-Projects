#ifndef DOUBLELINKNODE_H
#define DOUBLELINKNODE_H

#include "node.h"

class DoubleLinkNode : public node
{
    public:
        DoubleLinkNode();//default constructor
        DoubleLinkNode(string r, int n, DoubleLinkNode * no, DoubleLinkNode * p): node(r, n){next = no; prev = p;} //overloaded constructor
        DoubleLinkNode(const DoubleLinkNode &n): node(n){prev = n.prev; next = n.next;} //copy constructor

        int getNumber(){return num;} // virtual override of the getNumber function
        //accessors and mutators
        void setPrev(DoubleLinkNode * p){prev = p;}
        void setNext(DoubleLinkNode * n){next = n;}
        DoubleLinkNode* getPrev(){return prev;}
        DoubleLinkNode* getNext(){return next;}

    protected:
        DoubleLinkNode* next;//protected next and prev
        DoubleLinkNode* prev;
};

#endif // DOUBLELINKNODE_H
