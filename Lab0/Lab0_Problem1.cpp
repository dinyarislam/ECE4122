/*
Author: Dinyar Islam
Class: ECE4122
Last Date Modified: 5 September 2022

Description: Lab 0 Problem 1

What is the purpose of this file?
The program uses the insertion stream operator and 
escape sequences to output a particular text on to the console.
*/

#include <iostream>
#include <string>
using namespace std;

/*
The main function: outputs a particular text on to the console

@return 0
*/
int main()
{
    string firstName = "Dinyar";
    string lastName = "Islam";
    cout << "My name is: " << firstName << " " << lastName << "\n"; //using \n escape sequence for new line
    cout << "This (\") is a double quote.\n"; //using \" escape sequence to output "
    cout << "This (\') is a single quote.\n"; //using \' escape sequence to output '
    cout << "This (\\) is a backslash.\n"; //using \\ escape sequence to output \
    cout << "This (/) is a forward slash.\n";
    return 0;
}
