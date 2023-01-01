/*
Author: Dinyar Islam
Class: ECE4122
Last Date Modified: 5 September 2022

Description: Lab 0 Problem 2: One more One 

What is the purpose of this file?
The program  continuously takes in a number n from the console and outputs to 
the console the number of 1's that must be added to the positive integer n before the process 
above ends. For reference, the process ends when 0 is entered.
*/

#include <iostream>
#include <climits>
#include <string>

//function definition
int numOnes(int n);

/*
The main function: determines if an input is valid or not and based on that
calls the numOnes() function to calculate the number of 1's that must be added 
to the positive integer n before the process above ends. It then either outputs
the calculated value or an error message based on the input. A valid input is any 
positive int upto INT_MAX.

@return 0
*/
int main() 
{
    std::string num;
    int n;
    int ones;
    bool invFlag;
    do 
    {
        invFlag = false;
        n = 0;
        std::cout << "Enter an integer: "; //prompt user to input value
        std::getline(std::cin, num);
        for (int i = 0; i < num.length(); i++) //check if input has ASCII characters other than digits
        {
            if (!isdigit(num[i]))
            {
                n = -1;
                invFlag = true;
                i = num.length();
            }

        }
        if (!invFlag) //If input is an int convert it from a string
        {
            n = stoi(num);
        }
        if (n > INT_MAX || n < 0) //Is input a positive int? If not error message
        {
            std::cout << "Invalid input!! Please try again.\n";
        }
        else if (n <= INT_MAX && n > 0) //If input valid call numOnes()
        {
            ones = numOnes(n);
            std::cout << "The sequence had " << ones << " instances of the number 1 being added.\n";
        }
    } while (n != 0);
    std::cout << "The program was ended as user entered zero.\n"; //End program if user enter 0 with ending message
    return 0;
}

/*
numOnes function: a recursive function that calculates the number 
of 1's that must be added to the positive integer n before the process 
ends when n = 1.

@param the integer n
@return number of 1's
*/
int numOnes(int n)
{
    if (n % 7 == 0) //If input is divisible by 7 call numOnes on n/7
    {
        n = n / 7;
        return numOnes(n) + 0;
    }
    else if (n == 1) { //If input is 1 return 0
        return 0;
    }
    else 
    {
        n++;
        return numOnes(n) + 1; //If input is not divisible by 7 and not 1, call numOnes() and increment the return value
    }
}