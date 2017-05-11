#include "LinkedList.h"

LinkedList::LinkedList() //default constructor
{
    head = nullptr;
    tail = nullptr;
}

void LinkedList::print(ofstream& outfile, DoubleLinkNode* ptr)//recursive print
{
    if (ptr == nullptr) //if at the end, return out of the function
        return;
    outfile << ptr; //output the node
    print(outfile, ptr->getNext()); //recursively go to next node
}

void LinkedList::operator+=(DoubleLinkNode *n) //overloaded += constructor
{
    if(head == nullptr) //if its the first, get up head and tail
    {
        head = n;
        tail = n;
    }
    else if(head->getNumber() == 0) //if the list is empty after deleting the only node
    {
        head->setNumber(n->getNumber());//set empty node to n's value and delete n
        head->setRoman(n->getRoman());
        delete n;
    }
    else
    {
        tail->setNext(n); //set next to the next node at the end of list
        n->setPrev(tail); //set prev of n to the end of the list
        tail = n; //move tail over
        n->setNext(nullptr); //setnext of the newly added node
    }
}

void LinkedList::operator--()//prefix delete first
{
    if(head == tail) //if it is the only node in the list, set values of it to 0
    {
        head->setRoman("");
        head->setNumber(0);
        return;
    }
    DoubleLinkNode *ptr = head; //set ptr to head
    head = head->getNext(); //move head
    delete ptr; //delete old head
    head->setPrev(nullptr); //set head's prev to nullptr
}

void LinkedList::operator--(int)//postfix delete last
{
    if(head == tail) //if it is the only node in the list, set values of it to 0
    {
        head->setRoman("");
        head->setNumber(0);
        return;
    }
    DoubleLinkNode *ptr = tail;//set ptr to tail
    tail = tail->getPrev(); //move tail
    delete ptr; //delete old tail
    tail->setNext(nullptr); //set tails next to nullptr
}

void LinkedList::deleteList(DoubleLinkNode* head)//loop through the whole list recursively and delete it all
{
    if(head == nullptr) //if head is deleted
        return;
    else
    {
        deleteList(head->getNext()); // recursively move through list
        delete head; //delete the head of the list back to front because of the stack
    }
}

LinkedList::~LinkedList()//destructor to call the delete function
{
    deleteList(head);
}
