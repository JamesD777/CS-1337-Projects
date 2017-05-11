#ifndef NODE_H
#define NODE_H


class node
{
    public:
        node(){next = nullptr;}//default constructor
        node(int e, double c, node*n){exp = e; coef = c; next = n;}
        int exp;
        double coef;
        node* next = nullptr;
        int getExp(){return exp;}//gets and sets for node
        double getCoef(){return coef;}
        node* getNext(){return next;}

        void setExp(int e){exp = e;}
        void setCoef(double c){coef = c;}
        void setNext(node*n){next = n;}
};

#endif // NODE_H
