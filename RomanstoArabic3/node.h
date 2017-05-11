#ifndef NODE_H
#define NODE_H
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;

class node
{
    public:
        node();//default constructor
        node(string r, int n){rom = r; num = n;} //overloaded constructor
        node(const node &n){rom = n.rom; num = n.num;} //node copy constructor

        virtual int getNumber() = 0;//virtual getnum to make this an abstract class
        string getRoman(){return rom;} //return roman

        void setNumber(int n){num = n;} //set number
        void setRoman(string r){rom = r;} //set roman
        friend istream& operator>>(istream& in, node *ptr); //overloaded input
        friend void operator<<(ostream& outfile, node*ptr); //overloaded output

    protected:
        string rom;//protected rom and num
        int num;

};

#endif // NODE_H
