#include "LinkedList.h"
#include <iostream>
#include <math.h>
#include <iomanip>

LinkedList::LinkedList()
{
}

    void LinkedList::Insert(node* h)
    {

		if(h->next == nullptr)//if first node
        {
            std::cout << std::endl << "first \n";
            head->setCoef(h->getCoef());
            head->setExp(h->getExp());
		}
        else
        {
            node *cur = head;//loop to end and add node to the list
            while(cur->next)
                cur = cur->next;
            h->next = nullptr;
            cur->next = h;
        }
    }

    void LinkedList::print(std::ofstream &out, node* n)//print recursively
    {
        if (n == nullptr)//if at end, stop
            return;
        if(n->getExp() == head->getExp())//if at the first term
        {
            if(n->getExp() == 0)//if exp is 0, print out just coef
            {
                out<< n->getCoef()<< " ";
                print(out, n->next);
            }
            else if(n->getCoef() > 0)//if coef is positive
            {
                if(n->getExp() == 1)//if exp is 1, print correctly
                {
                    if(n->getCoef() != 1)//if coef is 1, print correctly
                    {
                        out<< " "<< n->getCoef()<<"x ";
                        print(out, n->next);
                    }
                    else
                    {
                        out<<" x ";
                        print(out, n->next);
                    }
                }
                else//if not 1, print correctly
                {
                    if(n->getCoef() != 1)
                    {
                        out<< " " << n->getCoef() << "x^" << n->getExp()<< " ";
                        print(out, n->next);
                    }
                    else
                    {
                        out<< " " << "x^" << n->getExp()<< " ";
                        print(out, n->next);
                    }
                }
            }
            else//if not positive term
            {
                if(n->getExp() == 1)//if exp is 1
                {
                    if(n->getCoef() != -1)//if coef is not one, print correctly
                    {
                        out<< n->getCoef()<<"x ";
                        print(out, n->next);
                    }
                    else//print correctly
                    {
                        out<<"- x ";
                        print(out, n->next);
                    }
                }
                else
                {
                    out<< n->getCoef() << "x^" << n->getExp()<< " ";
                    print(out, n->next);
                }
            }
        }
        else//if not first term
        {
            if(n->getExp() == 0)//if exp is 0, print correctly
            {
                if(n->getCoef() > 0)
                {
                    out<< "+ " << n->getCoef()<< " ";
                    print(out, n->next);
                }
                else
                {
                    out<< n->getCoef()<< " ";
                    print(out, n->next);
                }
            }
            else if(n->getCoef() > 0)//print correctly if pos
            {
                if(n->getExp() == 1)
                {
                    if(n->getCoef() != 1)
                    {
                        out<< "+ "<< n->getCoef()<<"x ";
                        print(out, n->next);
                    }
                    else
                    {
                        out<<"+ x ";
                        print(out, n->next);
                    }
                }
                else
                {
                    if(n->getCoef() != 1)
                    {
                        out<< "+ " << n->getCoef() << "x^" << n->getExp()<< " ";
                        print(out, n->next);
                    }
                    else
                    {
                        out<< "+ " << "x^" << n->getExp()<< " ";
                        print(out, n->next);
                    }
                }
            }
            else//print correctly if neg
            {
                if(n->getExp() == 1)
                {
                    if(n->getCoef() != -1)
                    {
                        out<< n->getCoef()<<"x ";
                        print(out, n->next);
                    }
                    else
                    {
                        out<<"- x ";
                        print(out, n->next);
                    }
                }
                else
                {
                    if(n->getCoef() != -1)
                    {
                        out<< n->getCoef() << "x^" << n->getExp()<< " ";
                        print(out, n->next);
                    }
                    else
                    {
                        out<< "- x^" << n->getExp()<< " ";
                        print(out, n->next);
                    }
                }
            }
        }
    }

    void LinkedList::expSort(node* &head)//bubble sort
    {
        node *lend = nullptr;//create pointer for the end of the list
        while(lend != head)//while not at the end
        {
            node *temp, *swap1;//create a pointers to switch and hold something temp
            swap1 = head;
            while( swap1->next != lend )//while not at end
            {
                if(swap1->getExp() < swap1->next->getExp())//if left is smaller than right
                {
                    node *swap2 = swap1->next;//swap
                    swap1->next = swap2->next;
                    swap2->next = swap1;
                    if(swap1 == head)//if at the start, swap with head
                    {
                        head = swap2;
                        swap1 = swap2;
                    }
                    else
                    {
                        swap1 = swap2;
                        temp->next = swap2;
                    }
                }
                temp = swap1;//set temp to swap
                swap1 = swap1->next;
            }
            // update the lend to the last sorted element:
            lend = swap1;
        }
    }

    double LinkedList::calculate(node* head, double num)//calc the sum
    {
        double sum;
        node *ptr = head;
        while(ptr->next != nullptr)//loop through the list and solve the terms
        {
            sum += (pow(num, ptr->getExp()) * ptr->getCoef());
            ptr = ptr->next;
        }
        sum += (pow(num, ptr->getExp()) * ptr->getCoef());//add last term
        return sum;
    }

    void LinkedList::deletelist(node* head)//loop through the whole list recursively and delete it all
    {
        if(head == nullptr)
            return;
        else
        {
            deletelist(head->next);
            delete head;
        }
    }

LinkedList::~LinkedList()//delete the linked list
{
        deletelist(head);
}
