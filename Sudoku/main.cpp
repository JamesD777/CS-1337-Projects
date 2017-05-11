#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


int isValid(int *ptr); //prototype
/* Print function used to testing
void print(int *ptr)//print the array
{
    for (int j = 0; j < 9; j++)
    {
        for (int i = 0; i < 9; i++)
        {
            cout << *(ptr+(j*9)+i) << " ";
        }
        cout << endl;
    }
}*/

string rCheck ( int *ptr)//Check a row for validity
{
    int *ptr2 = new int[9];//temp array
    string String;
    for (int i=0; i<9; i++)
    {
        for (int j= 0; j<9; j++)
            *(ptr2+j) = *(ptr+(i*9)+j); //add values of the row into the temp array
        if (isValid(ptr2) >= 1) //if not valid row
        {
            String = static_cast<ostringstream*>( &(ostringstream() << isValid(ptr2)) )->str();//add together the numbers and the string
            String += " in row ";
            String += static_cast<ostringstream*>( &(ostringstream() << i+1) )->str();
            delete[] ptr2;//delete temp array memory allocation
            return String; //return the concatenated string
        }
    }
    delete[] ptr2; //if it gets through, delete memory allocation
    return "valid"; //return valid
}

int isValid(int *ptr2) //Checks if sent array pointer has any duplicates in it
{
    int numcheck;
    for (int i=0; i<9; i++)
    {
        numcheck = *(ptr2+i); //set the number as the number check
        for (int j=i+1; j<9; j++) //checks all values in array to the numcheck value
        {
            if (*(ptr2+j) ==  numcheck) //if duplicate is found, return it
            {
                return numcheck;
            }
        }
    }
  return 0; //else return 0 if array is valid
}

//Checks for duplications in columns
string cCheck (int *ptr)
{
    int *ptr2 = new int[9]; //memory allocation for temp array
    string String;
    for(int i=0; i<9; i++)
    {
        for(int j= 0; j<9; j++)
            *(ptr2+j) = *(ptr+(j*9)+i); //set values of each column to the temp array
        if(isValid(ptr2) >= 1)//if not valid
        {
            String = static_cast<ostringstream*>( &(ostringstream() << isValid(ptr2)) )->str();//concatenate the string with numbers
            String += " in column ";
            String += static_cast<ostringstream*>( &(ostringstream() << i+1) )->str();
            delete[] ptr2; //delete allocation
            return String;//return error
        }
    }
    delete[] ptr2;//delete allocation
    return "valid"; //return valid if no duplicates are found
}


string squCheck (int *ptr) //check square for duplicates
{
    string Positioninsudoku; //string for which subsection error is found in
    int *ptr2 = new int[9]; //memory allocation for temp array
    int k;
    for(int row=0; row <= 6; row += 3)//loop through each 3x3 row
    {
        for(int column=0; column <= 6; column += 3) //loop through each column 3x3
        {
            k = 0;
            for(int i = 0; i < 3; i++) //loop through each row
            {
                for(int j=0; j < 3; j++)
                {
                    *(ptr2+k) = *(ptr+((row+i)*9)+(column+j)); //arr[row+i][column+j]; Add square values to the temp array
                    k++;
                }
            }
            if(isValid(ptr2) >= 1) //if error is found, return the error and where it is
            {
                if( row == 0 && column == 0)
					Positioninsudoku = " upper left";
				else if( row == 0 && column == 3)
					Positioninsudoku = " upper middle";
				else if( row == 0 && column == 6)
					Positioninsudoku = " upper right";
				else if( row == 3 && column == 0)
					Positioninsudoku = " middle left";
				else if( row == 3 && column == 3)
					Positioninsudoku = " middle";
				else if( row == 3 && column == 6)
					Positioninsudoku = " middle right";
				else if( row == 6 && column == 0)
					Positioninsudoku = " bottom left";
				else if( row == 6 && column == 3)
					Positioninsudoku = " bottom middle";
				else if( row == 6 && column == 6)
					Positioninsudoku = " bottom right";
				ostringstream convert;
                convert << isValid(ptr2); //convert int to string
                delete[] ptr2;//delete allocated memory for the array
				return convert.str() + "s in" + Positioninsudoku; //return error
            }
        }
    }
    delete[] ptr2; //delete memory allocation
	return "valid"; //return valid if no error found
}



int main()
{
    int *pntr = new int[81]; //array allocation for the sudoku puzzle
    ifstream file("puzzles.txt"); //input file to get puzzles
    ofstream out("solutions.txt"); //output file for errors
    int puzzleNum; //puzzle number
    int lineNum; //int to hold the line of numbers

    while(file.good()) //while good and not at the end
    {
        if (file.is_open()) //if input file is open
        {
                file >> puzzleNum; //get puzzle num
                for (int i=0; i<9; i++)
                {
                    file >> lineNum;
                    for (int j=8; j>=0; j--) //loop through and input the puzzle numbers into the array last to first
                    {
                        *(pntr+(i*9)+j) = lineNum % 10;//get last digit and put into array
                        lineNum = lineNum / 10;//divide big number by 10 to throw away the last digit we just used
                    }
                }
          // print(pntr); //prints the sudoku read and stored
        }

        if(out.is_open()) //checks if output file is open
        {
            if(squCheck(pntr) != "valid") //if square check isnt valid...
            {
                out << puzzleNum << "\tinvalid\t\tmultiple " << squCheck(pntr) << endl; //output error
            }
            else if(rCheck(pntr) != "valid")//if row isnt valid...
            {
                out << puzzleNum << "\tinvalid\t\tmultiple " << rCheck(pntr) << endl;//output error
            }
            else if(cCheck(pntr) != "valid") //if column isnt valid...
            {
                out << puzzleNum << "\t\tinvalid\t\tmultiple " << cCheck(pntr) << endl;//output error
            }
            else
                out << puzzleNum << "\t" << "valid" << endl;//output valid if no errors
        }
    }
    file.close();//close input file
    out.close();//close output file
    delete[] pntr;//delete allocated memory
    return 0;
}
