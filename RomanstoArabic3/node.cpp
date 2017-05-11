#include "node.h"
#include <sstream>
#include <iostream>
#include <string>

node::node()//default constructor
{
    rom = "";
    num = 0;
}
void operator<<(ostream& outfile, node*ptr)//output operator overloaded
{
    if(ptr->num == 0)//if list is empty, dont print anything
        return;
    outfile <<left<< setw(16) << ptr->rom << setw(4) << ptr->num << endl;//output to file the node
}

istream& operator>>(istream& in, node *ptr)//input operator overloaded
{
    string sear = "";//get an input
    std::cout << "\nInput an Arabic or Roman Value: ";
    std::cin >> sear;
    if((int)sear[0] >= 65 && (int)sear[0]<=90)//if roman
        ptr->rom = sear; //set roman
    else//if num
    {
        int choice;
        stringstream toin(sear);//use stringstream to convert the string to an int
        toin >> choice;
        ptr->num = choice;//input
    }
    return in;//return input stream
}
