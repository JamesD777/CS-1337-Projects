#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <iomanip>

//BINARY SEARCH LINES 312 - 341, CALL LINE 375 & 407
//INPUT VALIDATION

using namespace std;


    struct node//node for linked list
    {
        int num;
        string rom;
        node *next;

    };

    node* copyList(node *current)//copy list for binary search sort
    {
        node *co = new node;//create new node

        co->num = current->num;
        co->rom = current->rom;
        co->next = nullptr;

        node *head = co;//set head to the new node

        current = current->next;
        while (current != nullptr)//loop through actual linked list till end, copy over the nodes
        {
            co = co->next = new node; // advance copy to the element being copied
            co->num = current->num;
            co->rom = current->rom;
            co->next = nullptr;
            current = current->next;
        }
        return head;//return head of copied list
    }

	//finds the number's matching roman
	string setNumber(int n)
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
	int setRoman(string str)
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

	void addNode(node* &head, string roman, int x)//creates a new node with inputted values
    {
         node *p = new node;//set up node
         node *ptr = head;
         p->num = x;
         p->rom = roman;

         p->next = nullptr;
         if(head == nullptr)//if this is the start one
            head = p;
         else
         {
             while(ptr->next != nullptr)//loop to end
             {
                ptr = ptr->next;
             }
             ptr->next = p;//add to end
         }
    }

    void numBSort(node* &head)//bubble sort
    {
        node *lend = nullptr;//create pointer for the end of the list
        while(lend != head)//white not at the end
        {
            node *temp, *swap1;//create a pointers to switch and hold something temp
            swap1 = head;
            while( swap1->next != lend )//while not at end
            {
                if(swap1->num > swap1->next->num)//if left is bigger than right
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

    void romBSort(node* &head)//roman bubble sort
    {
        node *lend = nullptr;//create pointer for the end of the list
        while(lend != head)//white not at the end
        {
            node *temp, *swap1;//create a pointers to switch and hold something temp
            swap1 = head;
            while( swap1->next != lend )//while not at end
            {
                if(swap1->rom > swap1->next->rom)//if left is bigger than right
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

    node* middleNode( node *startNode , node *endNode) //function to find the middle node
    {
        int count = 0;
        node* ptr = startNode;//set pointer to start
        while ( ptr != endNode)//while not at end, count size
        {
            ptr = ptr->next;
            count++;
        }
        for(int i = 0; i<count/2; i++)//loop through to middle node
        {
            startNode = startNode->next;
        }
        return startNode;//return middle node

    }

    node* numBSearch( node* head, int valueToSearch) //binary search
    {
        node* startn = head;//create pointers for the left and right values of binary search
        node* endn = nullptr;
        do
         {
             node* middlen = middleNode( startn , endn); //calculate middle node

             if( middlen == nullptr ) // searched value not found
                return nullptr;
             if( middlen->num == valueToSearch ) //if middle value is the search term, return the value and be happy
                return middlen;
             else if ( middlen->num < valueToSearch ) //if middle num is less that search value, move start node to middle +1
                startn = middlen->next;//search first half
             else //else move end to middle
                endn = middlen;// need to search in end half
         }while(endn != startn ); //repeat while end is null or left search node isnt to the right of the right search node
         return nullptr;  // value not found
    }

    void deleteList(node* head)//delete list
    {
        while(head != nullptr)//while head points to a node
        {
            node* old = head;//set node to head
            head = head->next;//move head up
            delete old;//delete old node
        }
    }

    void UI(node* &head)//UI
    {
        node* head2;//copy list head
        bool UII = true, UII2 = true, numTest;//bool for UI loop, and num valid test
        int choice;//choice gotten from input for UI
        string sear;//search input
        while (UII)
        {
            cout<<"\n1. Search\n2. Sort\n3. Quit\n";
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
                case 1:
                    cout<<"\n Enter a Search item: ";
                    cin.ignore();
                    getline(cin,sear);//get the input

                    if((int)sear[0] >= 65 && (int)sear[0]<=90)//if roman
                    {
                        if(validate(sear))//validate inputted roman
                        {
                            head2 = copyList(head);//create copy
                            numBSort(head2);//run bubble sort
                            if (numBSearch(head2, setRoman(sear)) != nullptr)//binary sort call
                                cout << endl<<"Roman Numeral "<<sear << " found in list!"<<endl;
                            else
                                cout << endl<<"Roman Numeral "<<sear << " is not in the list!"<<endl;
                            deleteList(head2);//delete copy
                        }
                        else
                            cout << "\nInvalid Roman. Try again! \n";
                    }
                    else if((int)sear[0] >= 49 && (int)sear[0]<=57)//if num
                    {
                        numTest = true;
                        for(unsigned int i = 0; i < sear.length(); i++)//check for only valid digits
                        {
                            if((int)sear[i] < 49 || (int)sear[i] > 57)
                            {
                                numTest = false;
                                cout << "Invalid Number"<<endl; //report error and break
                                break;
                            }
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
                            head2 = copyList(head);//create copy
                            numBSort(head2);//sort list
                            if (numBSearch(head2, choice) != nullptr)//binary sort list
                            {
                                cout << endl<<"Number "<<choice << " found in list!"<<endl;
                            }
                            else
                                cout << endl<<"Number "<<choice << " is not in the list!"<<endl;
                            deleteList(head2);//delete copy
                        }
                    }
                    else//is invalid
                        cout << "\nInvalid input. Try again! \n";
                    break;
                case 2://sort
                    UII2 = true;
                    while (UII2)
                    {
                        cout<<"\n1.Sort by Roman numeral\n2.Sort by Arabic numeral:\n";
                        cin>>sear;
                        if(sear.length() > 1)//check for valid num length for input
                            choice = 4;
                        else
                        {
                            stringstream toint(sear);//use stringstream to convert the substring of the line to an int
                            toint >> choice;
                        }
                        node *p;
                        switch(choice)
                        {
                            case 1:
                                romBSort(head);
                                p = head;//pointer to print out sorted list
                                if(head == nullptr)//if empty
                                    cout<<"\nNothing to Display\n";
                                else
                                {
                                    while(p!= nullptr)//till the end of the linked list, print romans
                                    {
                                        cout<< endl << p->rom;
                                        p = p->next;
                                    }
                                }
                                delete p;//clean up
                                UII2 = false;
                                break;
                            case 2://roman sort, see pseudo above
                                numBSort(head);
                                p = head;
                                if(head == nullptr)
                                    cout<<"\nNothing to Display\n";
                                else
                                {
                                    while(p!= nullptr)
                                    {
                                        cout<< endl << p->num;
                                        p = p->next;
                                    }
                                }
                                delete p;
                                UII2 = false;
                                break;
                            default:
                                cin.clear();
                                cin.ignore(256, '\n');//ignore anything not wanted
                                cout << "\nInvalid Sort Input. Try again! \n";//invalid sort input
                                break;
                        }
                    }
                    break;
                case 3://get out of UI
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
        string roman;
        string line;
        int i;
        bool endoffile = false;
        ifstream myfile;
        bool flag;
        string part;
        node *head = nullptr;

        myfile.open("numbers.txt"); //open file
        if(myfile.is_open()) //if open
        {
            while(!myfile.eof())//if not at end
            {
                flag = true;
                getline(myfile, line); //take out the line
                if(myfile.tellg() == -1) //if no new line char at the end of the line
                    endoffile = true; //set bool for later

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
                        addNode(head, setNumber(i), i);//add node to the linked list
                    }
                }
                else
                {
                    if(validate(line.substr(0, 16)))//if valid roman
                        addNode(head, line.substr(0, 16), setRoman(line.substr(0, 16)));//add node to the linked list
                }
                if(endoffile)//if the file is completed, break out of an infinite loop
                    break;
            }
            UI(head);//call UI up
            myfile.close();//close file
            ofstream outfile;//open utput file
            outfile.open("numbers.txt"); //open file
            node* ptr = head;
            while(ptr->next != nullptr)//while not at end of linked list
            {
                outfile <<left<< setw(16) << ptr->rom << setw(4) << ptr->num << endl;//output formatted answers to file
                ptr = ptr->next;
            }
            outfile <<left<< setw(16) << ptr->rom << setw(4) << ptr->num << endl;//output formatted answers to file
            delete ptr;//delete ptr
            deleteList(head);//delete linked list
            delete head;//delete head of linked list
            cout<< "k";
            outfile.close();//close file
        }
        return 0;
    }
