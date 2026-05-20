#include <iostream>
#include <iomanip> // Header file for setw() function.

using namespace std;

int main(){
    // Constant in C++
    int x = 34; // This is a variable.
    const float pi = 3.1415; // This is a constant and it's value can't be re-assigned, or you will get an error.
    // pi = 3.11; // Not allowed.
    cout<<"Value of PI = "<<pi<<endl;

    // ********** Manipulators in C++ **********
    int a1 = 12, b1 = 53, c1 = 25384345;
    cout<<"The value of a1 is: "<<a1<<endl; // Without setw()
    cout<<"The value of b1 is: "<<b1<<endl; // Without setw()
    cout<<"The value of c1 is: "<<c1<<endl; // Without setw()
    cout<<endl;
    cout<<"The value of a1 is: "<<setw(4)<<a1<<endl; // With setw()
    cout<<"The value of b1 is: "<<setw(4)<<b1<<endl; // With setw()
    cout<<"The value of c1 is: "<<setw(4)<<c1<<endl; // With setw()
    // Summery: 1. endl --> used to flush the buffer and print \n
    //          2. setw() --> used to set the normal width in cout function. if the width of the variable is greater than setw()'s width then cout will print the remaining value at the end.

    // ********** Operator Precedence **********
    int a2 = 3, b2 = 4;
    int c2 = (a2-5)*b2; // This will output -8
    cout<<c2<<endl;
    c2 = a2-5*b2; // This will output -17
    cout<<c2<<endl;
    // Summery: BODMAS: Bracket --> Of --> Division --> Multiplication --> Addition --> Subtraction
    //          C++: Bracket --> Multiplication, Division, Reminder(modulo) --> Addition,Subtraction     Left to Right.
    return 0;
}