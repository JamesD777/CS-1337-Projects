#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;


    struct node
    {
        int num;
        string rom;
        node *next;

    };
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

	bool validate(string part)
	{
	    bool flag = true;
	    part.erase(find_if(part.rbegin(), part.rend(), bind1st(not_equal_to<char>(), ' ')).base(), part.end()); //remove trailing spaces
                    for(unsigned int n = 0; n<part.length()-1; n++)
                    {
                        cout << endl<< part[n]<<endl<<endl;
                        switch(part[n])
                        {
                            case 'I':
                                if(part[n+1] != 'I' && part[n+1] != 'V' && part[n+1] != 'X')
                                {
                                    cout << "stuck I"<<endl;
                                    flag = false;
                                }
                                break;
                            case 'V':
                                if(part[n+1] != 'I')
                                {
                                    cout << "stuckV"<<endl;
                                    flag = false;
                                }
                                break;
                            case 'X':
                                if(part[n+1] != 'I' && part[n+1] != 'V' && part[n+1] != 'X' && part[n+1] != 'C' && part[n+1] != 'L')
                                {
                                    cout << "stuckX"<<endl;
                                    flag = false;
                                }
                                break;
                            case 'L':
                                if(part[n+1] != 'I' && part[n+1] != 'V' && part[n+1] != 'X')
                                {
                                    cout << "stuckL"<<endl;
                                    flag = false;
                                }
                                break;
                            case 'C':
                                if(part[n+1] != 'I' && part[n+1] != 'V' && part[n+1] != 'X' && part[n+1] != 'L' && part[n+1] != 'C' && part[n+1] != 'M' && part[n+1] != 'D')
                                {
                                    cout << "stuckC"<<endl;
                                    flag = false;
                                }
                                break;
                            case 'D':
                                if(part[n+1] != 'I' && part[n+1] != 'V' && part[n+1] != 'X' && part[n+1] != 'L' && part[n+1] != 'C')
                                {
                                    cout << "stuckD"<<endl;
                                    flag = false;
                                }
                                break;
                            case 'M':
                                if(part[n+1] != 'I' && part[n+1] != 'V' && part[n+1] != 'X' && part[n+1] != 'L' && part[n+1] != 'D' && part[n+1] != 'M' && part[n+1] != 'C')
                                {
                                    cout << "stuckM"<<endl;
                                    flag = false;
                                }
                                break;
                            default:
                                cout << "stuckdefault"<<endl;
                                break;
                        }
                    }
        return flag;
	}

	void Print(node* &head)
    {
        node *p = head;
        if(head == NULL)
            cout<<"\nNothing to Display\n";
        else
        {
            while(p!= nullptr)
            {
                cout<<endl<<p->num;
                p = p->next;
            }
        }
        delete p;
    }

    int main()
    {
        string roman;
        string line;
        int i;
        bool endoffile = false;
        fstream myfile;
        bool flag;
        string part;

        myfile.open("numbers.txt", ios::in | ios::out | ios::binary); //open file
        if(myfile.is_open()) //if open
        {
            while(!myfile.eof())//if not at end
            {
                flag = true;
                getline(myfile, line); //take out the line

                if(myfile.tellg() == -1) //if no new line char at the end of the line
                {
                    endoffile = true; //set bool for later
                }

                if(line[0] == ' ') //if space exists at the start of the line
                {
                    part = line.substr(16, 20);
                    cout << part<<endl<<part<<endl<<part<<endl;
                    //part.erase(find_if(part.rbegin(), part.rend(), bind1st(not_equal_to<char>(), ' ')).base(), part.end()); //remove trailing spaces
                    cout << part << "k";
                    for(int m = 0; m<3;m++)
                    {
                        if((part[m] == ' ' && part[m+1] != ' ') || (int)part[m] <= 47 || (int)part[m] >= 58)
                        {
                           flag = false;
                           cout<< " ERRROR" << (int)part[m]<<endl;
                           break;
                        }
                    }
                    if(!flag && endoffile)
                    {
                        break;
                    }
                    else if(!flag)
                    {
                        continue;
                    }
                    else
                    {
                        stringstream toint(part);//use stringstream to convert the substring of the line to an int
                        toint >> i;
                        if(i > 4999 || i < 1)//if number is out of range because mr. smith is slightly evil
                        {
                            cout << "Number out of range"<<endl; //report error and break
                            continue;
                        }
                        cout << endl <<"WOOOOOOWOOOOOOOOOOOOW   "<< i<<endl;
                        line = setNumber(i) + line.substr(setNumber(i).length(), 20); //concatenate the given roman to the start of the line

                        if (endoffile) //if at last line
                        {
                            myfile.close(); //close file to avoid lines not outputting to file incorrectly (CSMC helped)
                            myfile.open("numbers.txt", ios::in | ios::out | ios::binary); //open file
                            myfile.seekg(-21,ios::end); //go to the start of the last line
                            myfile << endl;//add a line to print the last line because the initial line that was there was deleted because C++ assumed we were done at the end of the file
                        }
                        else
                        {
                            myfile.seekg(-22, ios::cur); //move pointer to the start of the line
                        }
                        myfile << line;//output line to file
                        getline(myfile, line); //get new just outputted so that the next getline call will get the line we need next
                    }
                }
                else
                {
                    flag = validate(line.substr(0, 16));

                    if(flag)
                    {
                        stringstream tostr; //use stringstream to convert gotten roman into an int after the roman conversion is completed
                        tostr << setRoman(line.substr(0, 16));
                        line = line.substr(0, 16) + tostr.str();//concatenate

                        if (endoffile)//if at last line
                        {
                            myfile.close();//close file to avoid lines not outputting to file incorrectly (CSMC helped)
                            myfile.open("numbers.txt", ios::in | ios::out | ios::binary);//open file
                            myfile.seekg(-21,ios::end);//go to the start of the last line
                            myfile << endl;//add a line to print the last line because the initial line that was there was deleted because C++ assumed we were done at the end of the file
                        }
                        else
                        {
                            myfile.seekg(-22, ios::cur);//move pointer to the start of the line
                        }
                        myfile << line;//output line to file
                        getline(myfile, line);//get new just outputted so that the next getline call will get the line we need next
                    }
                }
                if(endoffile)//if the file is completed, break out of an infinite loop
                {
                    break;
                }
            }
            myfile.close();//close file
        }
        return 0;
    }
