#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "DoubleLinkNode.h"
#include <fstream>
#include <iostream>
class LinkedList
{
    public:
        LinkedList(); //default constructor
        LinkedList(DoubleLinkNode *h){head = h; tail = h;} //overloaded constructor
        void deleteList(DoubleLinkNode* head);//delete list recursively
        //accessors and mutators
        DoubleLinkNode* getTail(){return tail;}
        DoubleLinkNode* getHead(){return head;}

        void setTail(DoubleLinkNode* t){tail = t;}
        void setHead(DoubleLinkNode* h){head = h;}
        void print(ofstream&, DoubleLinkNode*);//print

        void operator+=( DoubleLinkNode *n); //add node
        void operator--();//prefix notation overloaded operator, delete first node
        void operator--(int); //postfix notation overloaded operator, delete last node

        ~LinkedList();

    private:
        DoubleLinkNode *head;//head and tail, private
        DoubleLinkNode *tail;

};

#endif // LINKEDLIST_H
