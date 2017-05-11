//DELETE ANY NODE line 414
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <iomanip>
#include "LinkedList.h"
#include "DoubleLinkNode.h"


using namespace std;


//finds the number's matching roman
string toRoman(int n)
{
    int NUMBERS [] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string LETTERS [] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int arsize = 13;
    string roman = "";

    //goes through each of the NUMBERS and only moves on when the number given is less than the value
    for (int i = 0; i < arsize; i++)
    {
        //while the number given is bigger than the biggest NUMBERS number
        while (n >= NUMBERS[i])
        {
            roman += LETTERS[i];
            n -= NUMBERS[i];
        }
    }
    return roman;
}

//finds the roman's matching number
int toNumber(string str)
{
    int Sum = 0;

    //for loop goes through roman cases and tests if str starts with it
    for(unsigned int i = 0; i < str.length(); i++) //unsigned to fix c++ warning
        if(str[i] == 'M')
            Sum += 1000;
        else if (str[i] == 'D')
            Sum += 500;
        else if (str[i] == 'C' && (str[i+1] == 'M' || str[i+1] == 'D'))
            Sum -= 100;
        else if (str[i] == 'C')
            Sum += 100;
        else if (str[i] == 'L')
            Sum += 50;
        else if (str[i] == 'X' && (str[i+1] == 'L' || str[i+1] == 'C'))
            Sum -= 10;
        else if (str[i] == 'X')
            Sum += 10;
        else if (str[i] == 'V')
            Sum += 5;
        else if (str[i] == 'I' && (str[i+1] == 'V' || str[i+1] == 'X'))
            Sum -= 1;
        else if (str[i] == 'I')
            Sum += 1;
    return Sum;
}

bool validate(string part)//validate roman numerals
{
    part.erase(find_if(part.rbegin(), part.rend(), bind1st(not_equal_to<char>(), ' ')).base(), part.end()); //remove trailing spaces

    for(unsigned int i = 0;i < part.length();i++)//loop through the roman
    {
        //make sure only valid ROMAN singles are in the string
        if(part[i] != ' ' && part[i] != 'I' && part[i] != 'V' && part[i] != 'X' && part[i] != 'L' && part[i] != 'C' && part[i] != 'D' && part[i] != 'M')
            return false;
        //validate I
        if(part[i] == 'I')
        {
            for(unsigned int j = i;j < part.length();j++)//second loop to loop through rest of string from each checking value
            {
                if(part[j] != 'I' && part[j] != 'V' && part[j] != 'X' && part[j] != ' ')//check for only valid following romans
                    return false;
                if(part[j] == 'X' && j > i+1) //if X is between 2 I's, return false
                    return false;
                if(part[j] == 'V' && j > i+1) //if V is between 2 I's, return false
                    return false;
            }
        }
        //validate V
        if(part[i] == 'V')
        {
            for(unsigned int j = i+1;j < part.length();j++)//second loop to loop through rest of string from each checking value
            {
                if(part[j] != 'I' && part[j] != ' ') //make sure only I follows
                    return false;
            }
        }
        //validate X
        if(part[i] == 'X')
        {
            for(unsigned int j = i+1;j < part.length();j++)//second loop to loop through rest of string from each checking value
            {
                if(part[j] != 'I' && part[j] != 'V' && part[j] != 'L' && part[j] != 'C' && part[j] != 'X' && part[j] != ' ')//check for valid romans after the X
                    return false;
                if(part[j] == 'C' && j > i+1)//no X before and after a C
                    return false;
                if(part[j] == 'L' && j > i+1)//no X before and after a L
                    return false;

                if(part[i+1] != 'L' && part[i+1] != 'C') //if L and C is not there
                {
                    if(part[j-1] != 'I' && j > i+2)//if I is not before X
                        if(part[j] == 'X' && j > i+2)//no X before and after
                            return false;
                }
            }
        }
        //validate L
        if(part[i] == 'L')
        {
            for(unsigned int j = i+1;j < part.length();j++)//second loop to loop through rest of string from each checking value
            {
                if(part[j] != 'I' && part[j] != 'V' && part[j] != 'X' && part[j] != ' ')//check for legit romans after L
                    return false;
            }
        }
        //validate C
        if(part[i] == 'C')
        {
            for(unsigned int j = i+1;j < part.length();j++)//second loop to loop through rest of string from each checking value
            {
                if(part[j] != 'I' && part[j] != 'V' && part[j] != 'X' && part[j] != 'C' && part[j] != 'D' && part[j] != 'L' && part[j] != 'M' && part[j] != ' ')//check for valid romans after C
                        return false;
                if(part[j] == 'M' && j > i+1)//check for M before and after C
                    return false;
                if(part[j] == 'D' && j > i+1)//check for D before and after C
                    return false;
                if(part[i+1] != 'M' && part[i+1] != 'D')//if not D and M
                {
                    if(part[j-1] != 'X')//if X is not before
                        if(part[j] == 'C' && j > i+2)//if C is repeated
                            return false;
                }
            }
        }
        //validate D
        if(part[i] == 'D')
        {
            for(unsigned int j = i+1;j < part.length();j++)//second loop to loop through rest of string from each checking value
            {
                if(part[j] != 'I' && part[j] != 'V' && part[j] != 'X'&& part[j] != 'C'&& part[j] != 'L' && part[j] != ' ')//check for valid romans after D
                    return false;
            }
        }
        //validate M
        if(part[i] == 'M')
        {
            for(unsigned int j = i+1;j < part.length();j++)//second loop to loop through rest of string from each checking value
            {
                if(part[j] != 'I' && part[j] != 'V' && part[j] != 'X'&& part[j] != 'C'&& part[j] != 'L'&& part[j] != 'D' && part[j] != 'M' && part[j] != ' ')//check for valid romans after
                    return false;
                if(part[j-1] != 'C')//if C is not before
                {
                    if(part[j] == 'M' && j > i+3)//does M repeat too much
                        return false;
                }
            }
        }

        char stRom[20];//check for special cases of 4 repeats, or 5 repeats for M
        strcpy(stRom,part.c_str());
        if(strstr(stRom,"IIII")|| strstr(stRom,"XXXX") || strstr(stRom,"CCCC") || strstr(stRom,"MMMMM") || strstr(stRom,"XLX") || strstr(stRom,"CDC") || strstr(stRom,"IVI") || strstr(stRom,"IXI") || strstr(stRom,"CMC") || strstr(stRom,"XCX"))
            return false;
    }
    return true;
}


void numBSort(LinkedList &LL)//bubble sort
{
    if(LL.getHead() != LL.getTail())
    {
        DoubleLinkNode *lend = nullptr;//create pointer for the end of the list
        while(lend != LL.getHead())//while not at the end
        {
            DoubleLinkNode *temp, *swap1;//create a pointers to switch and hold something temp
            swap1 = LL.getHead();
            while(swap1->getNext() != lend )//while not at end
            {
                if(swap1->getNumber() > swap1->getNext()->getNumber())//if left is bigger than right
                {
                    DoubleLinkNode *swap2 = swap1->getNext();//swap
                    swap1->setNext(swap2->getNext());
                    swap2->setNext(swap1);
                    if(swap1 == LL.getHead())//if at the start, swap with head
                    {
                        LL.setHead(swap2);
                        swap1 = swap2;

                    }
                    else
                    {
                        swap1 = swap2;
                        temp->setNext(swap2);
                    }
                }
                temp = swap1;//set temp to swap
                swap1 = swap1->getNext();
            }
            // update the lend to the last sorted element:
            lend = swap1;
        }
        lend = LL.getHead();
        lend->setPrev(nullptr);
        DoubleLinkNode *ptr = lend;
        ptr = lend->getNext();
        while(ptr->getNext() != nullptr)//while not at end of linked list
        {
            ptr->setPrev(lend); //loop through linked list and set up prev's
            ptr = ptr->getNext();
            lend = lend->getNext();//move ptr
        }
        ptr->setPrev(lend);//set last node's prev
        LL.setTail(ptr);//set tail to end
    }
}

void RomBSort(LinkedList &LL)//bubble sort
{
    DoubleLinkNode *lend = nullptr;//create pointer for the end of the list
    while(lend != LL.getHead())//while not at the end
    {
        DoubleLinkNode *temp, *swap1;//create a pointers to switch and hold something temp
        swap1 = LL.getHead();
        while(swap1->getNext() != lend )//while not at end
        {
            if(swap1->getRoman() > swap1->getNext()->getRoman())//if left is bigger than right
            {
                DoubleLinkNode *swap2 = swap1->getNext();//swap
                swap1->setNext(swap2->getNext());
                swap2->setNext(swap1);
                if(swap1 == LL.getHead())//if at the start, swap with head
                {
                    LL.setHead(swap2);
                    swap1 = swap2;

                }
                else
                {
                    swap1 = swap2;
                    temp->setNext(swap2);
                }
            }
            temp = swap1;//set temp to swap
            swap1 = swap1->getNext();
        }
        // update the lend to the last sorted element:
        lend = swap1;
    }
    lend = LL.getHead();
    lend->setPrev(nullptr);//set head's prev to nullptr
    DoubleLinkNode *ptr = lend;
    ptr = lend->getNext();
    while(ptr->getNext() != nullptr)//while not at end of linked list
    {
        ptr->setPrev(lend);//set up prevs
        ptr = ptr->getNext();
        lend = lend->getNext();//move ptr
    }
    ptr->setPrev(lend);//set the ends prev
    LL.setTail(ptr); //set tail to end
}

DoubleLinkNode* middleNode(DoubleLinkNode *startNode , DoubleLinkNode *endNode) //function to find the middle node
{
    int count = 0;
    DoubleLinkNode* ptr = startNode;//set pointer to start
    while ( ptr != endNode)//while not at end, count size
    {
        ptr = ptr->getNext();
        count++;
    }
    for(int i = 0; i<count/2; i++)//loop through to middle node
    {
        startNode = startNode->getNext();
    }
    return startNode;//return middle node

}

DoubleLinkNode* numBSearch( DoubleLinkNode* head, int valueToSearch) //binary search
{
    DoubleLinkNode* startn = head;//create pointers for the left and right values of binary search
    DoubleLinkNode* endn = nullptr;
    do
     {
         DoubleLinkNode* middlen = middleNode( startn , endn); //calculate middle node

         if( middlen == nullptr ) // searched value not found
            return nullptr;
         if( middlen->getNumber() == valueToSearch ) //if middle value is the search term, return the value and be happy
            return middlen;
         else if ( middlen->getNumber() < valueToSearch ) //if middle num is less that search value, move start node to middle +1
            startn = middlen->getNext();//search first half
         else //else move end to middle
            endn = middlen;// need to search in end half
     }while(endn != startn ); //repeat while end is null or left search node isnt to the right of the right search node
     return nullptr; // value not found
}

void UI(LinkedList &LL)//UI
{
    DoubleLinkNode *head = LL.getHead();
    bool UII = true, numTest;//bool for UI loop, and num valid test
    int choice;//choice gotten from input for UI
    string sear;//search input
    while (UII)
    {
        cout<<"\n1. Search\n2. Add\n3. Delete First\n4. Delete Last\n5. Delete Specific Item\n6. Exit\n";
        sear = "";
        cin>>sear;

        if(sear.length() > 1)//if input is greater than 1 num, say invalid
            choice = 4;
        else
        {
            stringstream toint(sear);//use stringstream to convert the substring of the sear to an int
            toint >> choice;
        }

        switch(choice)
        {
            case 1: //search for user inputted data
                cout<<"\n Enter a Search item: ";
                cin.ignore();
                getline(cin,sear);//get the input

                if((int)sear[0] >= 65 && (int)sear[0]<=90)//if roman
                {
                    if(validate(sear))//validate inputted roman
                    {
                        numBSort(LL);
                        head = LL.getHead();
                        if (numBSearch(head, toNumber(sear)) != nullptr)//binary sort call
                            cout << endl<<"Roman Numeral "<<sear << " found in list!"<<endl;
                        else
                            cout << endl<<"Roman Numeral "<<sear << " is not in the list!"<<endl;
                    }
                    else
                        cout << "\nInvalid Roman. Try again! \n";
                }
                else if((int)sear[0] >= 49 && (int)sear[0]<=57)//if num
                {
                    numTest = true;
                    for(unsigned int i = 0; i < sear.length(); i++)//check for only valid digits
                    {
                        if((int)sear[i] < 48 || (int)sear[i] > 57) //if not valid number
                        {
                            numTest = false;
                            cout << "Invalid Number"<<endl; //report error and break
                            break;
                        }
                    }
                    if((int)sear[0] == 48) //if 0
                    {
                        numTest = false;
                        cout << "Invalid Number"<<endl; //report error and break
                    }
                    stringstream toin(sear);//use stringstream to convert the string to an int
                    toin >> choice;
                    if(choice > 4999 || choice < 1)//if number is out of range because mr. smith is slightly evil
                    {
                            cout << "Number out of range"<<endl; //report error and break
                            numTest = false;
                    }
                    if(numTest)//if valid num
                    {
                        numBSort(LL);
                        head = LL.getHead();
                        if (numBSearch(head, choice) != nullptr)//binary sort list
                        {
                            cout << endl<<"Number "<<choice << " found in list!"<<endl;
                        }
                        else
                            cout << endl<<"Number "<<choice << " is not in the list!"<<endl;
                    }
                }
                else//is invalid
                    cout << "\nInvalid input. Try again! \n";
                break;
            case 2: //add a node to the end of the list
            {
                DoubleLinkNode *New = new DoubleLinkNode();
                cin >> New; //overloaded >> to set the inputted value
                if(New->getNumber() != 0) //if number was inputted, convert it and set up the roman
                    New->setRoman(toRoman(New->getNumber()));
                else //else do opposite
                    New->setNumber(toNumber(New->getRoman()));
                LL += New; //overloaded += add the node to the end of the list
                numBSort(LL); //sort
                cout << "\nNode Added!\n";
                break;
            }
            case 3://Delete First
                numBSort(LL); //sort
                --LL; //overloaded -- prefix, delete first
                cout << "\nFirst Node Deleted!\n";
                break;
            case 4://Delete Last
                numBSort(LL); //sort
                LL--; //overloaded -- delete last
                cout << "\nLast Node Deleted!\n";
                break;
            case 5://delete somewhere in list
            {
                numBSort(LL); //sort
                sear = "";
                cout<<"\nInsert a value you would like to remove: ";
                cin >> sear; //get used input
                if((int)sear[0] >= 65 && (int)sear[0]<=90)//if roman
                {
                    head = LL.getHead();
                    if (numBSearch(head, toNumber(sear)) != nullptr)//binary search call
                    {
                            DoubleLinkNode *ptr = LL.getHead();
                            while(ptr->getNext() != nullptr) //loop through list
                            {
                                if(ptr->getRoman() == sear) //if number is found
                                {
                                    if(ptr == LL.getHead()) //if head, delete head
                                    {
                                        --LL;
                                        cout << "\nRoman Numeral "<< sear << " is in the list and is now deleted!\n";
                                        sear = "";
                                        break;
                                    }
                                    else //else delete the node in the list
                                    {
                                        ptr->getPrev()->setNext(ptr->getNext());
                                        ptr->getNext()->setPrev(ptr->getPrev());
                                        cout << "\nRoman Numeral "<< sear << " is in the list and is now deleted!\n";
                                        sear = "";
                                        break;
                                    }
                                }
                                ptr = ptr->getNext(); //move through the list
                            }
                            if(LL.getHead()->getRoman() == sear) // if the list only has one node and it is the value we are searching for
                            {
                                if(ptr == LL.getHead())
                                {
                                    LL--; //delete the node
                                    cout << "\nRoman Numeral "<< sear << " is in the list and is now deleted!\n";
                                    sear = "";
                                }
                            }
                            else if(LL.getTail()->getRoman() == sear) // if the last node is the value we are searching for
                            {
                                if(ptr == LL.getTail()) //if tail, delete tail
                                {
                                    LL--;
                                    cout << "\nRoman Numeral "<< sear << " is in the list and is now deleted!\n";
                                    sear = "";
                                }
                            }
                            delete ptr; //delete the node that was found
                    }
                    else
                        cout << "\nRoman Numeral "<< sear << " is not in the list!\n";
                }
                else if((int)sear[0] >= 49 && (int)sear[0]<=57)//if num
                {
                    stringstream toin(sear);//use stringstream to convert the string to an int
                    toin >> choice;
                    head = LL.getHead();
                    if (numBSearch(head, choice) != nullptr)//binary search list
                    {
                            DoubleLinkNode *ptr = LL.getHead();
                            while(ptr->getNext() != nullptr) //loop through list
                            {
                                if(ptr->getNumber() == choice) //if found
                                {
                                    if(ptr == LL.getHead()) //if head, delete head
                                    {
                                        --LL;
                                        cout << "\nNumber "<< choice << " is in the list and is now deleted!\n";
                                        choice = 0;
                                        break;
                                    }
                                    else //else, delete the node
                                    {
                                        ptr->getPrev()->setNext(ptr->getNext());
                                        ptr->getNext()->setPrev(ptr->getPrev());
                                        cout << "\nNumber "<< choice << " is in the list and is now deleted!\n";
                                        choice = 0;
                                        break;
                                    }
                                }
                                ptr = ptr->getNext(); //move through list
                            }
                            if(LL.getHead()->getRoman() == toRoman(choice)) //if the list only has one node and it is what we searched for
                            {
                                if(ptr == LL.getHead()) //delete
                                {
                                    LL--;
                                    cout << "\nNumber "<< choice << " is in the list and is now deleted!\n";
                                }
                            }
                            else if(choice != 0){
                            if(ptr->getNumber() == choice) //if the value is in the last node
                            {
                                if(ptr == LL.getTail())//if tail, delete tail
                                {
                                    LL--;
                                    cout << "\nNumber "<< choice << " is in the list and is now deleted!\n";
                                    choice = 0;
                                    break;
                                }
                            }
                            }
                            delete ptr; //delete the node
                    }
                    else
                        cout << "\nNumber "<< choice << " is not in the list!\n";
                }
                else
                    cout << "\nInvalid input\n";
                sear = "";
                break;
            }
            case 6://get out of UI
                UII = false;
                break;
            default: //invalid UI input
                cin.clear();
                cin.ignore(256, '\n');
                cout<<"\nInvalid UI Option Input. Try again! \n";
                break;
        }
    }
}

    int main()
    {
        string line;
        int i;
        bool endoffile = false;
        ifstream myfile;
        bool flag;
        string part;
        LinkedList LL;

        myfile.open("numbers.txt"); //open file
        if(myfile.is_open()) //if open
        {
            while(!myfile.eof())//if not at end
            {
                flag = true;
                getline(myfile, line); //take out the line
                if(myfile.tellg() == -1) //if no new line char at the end of the line
                    endoffile = true; //bool for later

                if(line[0] == ' ') //if space exists at the start of the line
                {
                    part = line.substr(16, 20);
                    stringstream toint(part);//use stringstream to convert the substring of the line to an int
                    toint >> i;
                    for(int m = 0; m<2;m++)//check for valid digits
                    {
                        if(i > 9)
                        {
                            if((part[m] == ' ' && part[m+1] != ' ') || (int)part[m] <= 47 || (int)part[m] >= 58)
                            {
                               flag = false;
                               break;
                            }
                        }
                    }
                    if(!flag && endoffile)//if invalid num and end of file
                        break;
                    else if(!flag)//ignore invalid num line
                        continue;
                    else
                    {
                        stringstream toint(part);//use stringstream to convert the substring of the line to an int
                        toint >> i;
                        if(i > 4999 || i < 1)//if number is out of range because mr. smith is slightly evil
                            continue;
                        DoubleLinkNode *New = new DoubleLinkNode(toRoman(i), i, nullptr, nullptr);
                        LL += New;
                    }
                }
                else
                {
                    if(line[16] == ' ') //if the roman is bigger than 16, skip
                    {
                        if(validate(line.substr(0, 16)))//if valid roman
                        {
                            DoubleLinkNode *New = new DoubleLinkNode(line.substr(0, 16), toNumber(line.substr(0, 16)), nullptr, nullptr); //create the node
                            LL += New; //add the node to the list using overloaded +=
                        }
                    }
                }
                if(endoffile)//if the file is completed, break out of an infinite loop
                    break;
            }
            numBSort(LL); //sort
            UI(LL);//call UI up
            myfile.close();//close file
            numBSort(LL); //sort

            ofstream outfile;//open utput file
            outfile.open("numbers.txt"); //open file

            LL.print(outfile, LL.getHead()); //recursively print the list

            outfile.close();//close file
        }
        return 0;
    }
