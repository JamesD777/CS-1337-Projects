#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
#include "node.h"
#include "LinkedList.h"
using namespace std;

int main()
{
    LinkedList List; //linked list obj
    double num;
    string part;
    double coef;

    string line;
    ifstream myfile;
    myfile.open("poly.txt");//open file
    ofstream out;
    out.open("answers.txt");//open out file
    if(myfile.is_open()) //if open
        {
            while(!myfile.eof())//if not at end
            {
                node* head = new node(0,0,nullptr);//create empty node
                node* New = head;//create pointer to head
                getline(myfile, line); //take out the line
                out << line.substr(0, line.find('=')+2);//send the f() to the file
                line += " K";//add a buffer to look for
                part = "";//reset part
                for(unsigned int i = line.find('(')+1; i < line.find(')'); i++)//get the x number
                {
                    part += line[i];
                }
                num = atof(part.c_str());
                line = line.substr(line.find(')')+4);//cut the f() out of the line
                while(line[0] != 'K')//while not at the end of the line
                {
                    part = "";
                    if(line[0] == '-' && (int)line[1] > 47 && (int)line[1]< 58)//if the first term is negative, get it
                    {
                        for(unsigned int i = 0; i < line.find(' '); i++)
                            part += line[i];
                    }
                    else if(line[0] == '-' || line[0] == '+')//else if a + or - is found, get it and get the #
                    {
                        part += line[0];
                        line = line.substr(line.find(' ') + 1);
                        for(unsigned int i = 0; i < line.find(' '); i++)
                            part += line[i];
                    }
                    else//else get the first positive term
                    {
                        for(unsigned int i = 0; i < line.find(' '); i++)
                            part += line[i];
                    }

                    if((part[0] == '+' && part[1] == 'x'))//if no coef, coef = 1
                        coef = 1;
                    else if(part[0] == '-' && part[1] == 'x')// if no coef and a negative, coef is -1
                        coef = -1;
                    else if(part[0] == '-' && part[1] == ' ' && part[2] == 'x')// if no coef and a negative, coef is -1
                        coef = -1;
                    else
                        coef = atof(part.c_str());//else get coef
                    if(part.find('^') != string::npos)//if there is an exponent get it
                        part = part.substr(part.find('x') + 2);
                    else if(part.find('x') == string::npos)//if no x, exp = 0
                       part = "0";
                    else
                        part = "1";

                node* c = List.getHead();//node pointer to head
                if(c->getCoef() == 0 && c->getExp() == 0 && c->getNext() == nullptr)//is first term
                {
                    if(coef == 0)//if coef is 0, skip
                    {
                        line = line.substr(line.find(" ") + 1);
                        continue;
                    }
                    else//assign first node
                    {
                        List.getHead()->setCoef( coef );
                        List.getHead()->setExp( atoi(part.c_str()) );
                        line = line.substr(line.find(" ") + 1);
                    }
                }
                else//if not first
                {
                    bool like = false; //var for if like term is found
                    if(coef == 0)//if 0, skip
                    {
                        line = line.substr(line.find(" ") + 1);
                        continue;
                    }
                    else if(List.getHead()->getExp() == atoi(part.c_str()))//if like term is first term
                    {
                        List.getHead()->setCoef( coef + List.getHead()->coef);
                        like = true;
                    }
                    else
                    {
                        while(c->next != nullptr)//loop through and look for like terms
                        {
                            if(c->getExp() == atoi(part.c_str()))
                            {
                                c->setCoef(coef + c->coef);
                                like = true;
                                break;
                            }
                            c = c->next;
                        }
                        if(c->getExp() == atoi(part.c_str()) && !like)//check last term
                            {
                                c->setCoef(coef + c->coef);
                                like = true;
                            }
                    }
                    if(!like)//if no like terms found, create node
                    {
                        node* emp;

                        New = new node(atoi(part.c_str()), coef, emp);
                        List.Insert(New);
                        New = emp;
                    }
                    line = line.substr(line.find(" ") + 1);//cut up the line
                }

            }

                List.expSort(List.head);//sort by exp
                List.print(out, List.getHead());//print
                out << " = " << fixed <<setprecision(3)<< List.calculate(List.getHead(), num) << endl;//output the answer
                node *cur = List.getHead();//loop through and move the temp head down
                while(cur->next)
                    cur = cur->next;
                head->next = nullptr;
                List.setHead(cur);
                List.getHead()->setCoef(0);
                List.getHead()->setExp(0);
                List.getHead()->next == nullptr;
            }
            myfile.close();//close file
            out.close();//close file
        }
        return 0;
    }
