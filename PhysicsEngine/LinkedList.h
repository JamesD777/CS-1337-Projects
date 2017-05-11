#include "node.h"
#include <fstream>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

class LinkedList
{
    public:
        LinkedList();//constructor
        LinkedList(node *h){head = h;}
        node *head = new node(0,0,nullptr);
        node *getHead(){return head;}//sets and gets
        void setHead(node* h){head = h;};
        double sum = 0;
        double getSum(){return sum;}
        double calculate(node* h, double num);//calc sum
        void Insert(node* h);//insert to linked list
        void expSort(node* &head);//bubble sort
        void print(std::ofstream &out, node* n);//print
        void deletelist(node *n);//delete

        ~LinkedList();
};

#endif // LINKEDLIST_H
