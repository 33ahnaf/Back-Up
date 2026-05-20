#include <iostream>
// "Do once use forever." -- A wise man.
using namespace std;
// int sum(int a, b); // --> Not Acceptable
// int sum(int a, int b); // --> Acceptable
int sum(int, int); // --> Acceptable
// void hello(void); // --> Acceptable
void hello(); // --> Acceptable

int main(){
    int num1, num2;
    cout << "Enter num1: ";
    cin >> num1;
    cout << "Enter num2: ";
    cin >> num2;
    int sum_of_nums = sum(num1, num2); // num1 and num2 are Actual Parameters.
    cout << "Sum of num1 and num2 = " << sum_of_nums << "\n";
    hello();
    return 0;
}

int sum(int x, int y){ // x and y are Formal Parameters which are taking values from actual parameter num1 and num2.
    int z = x+y;
    return z;
}

void hello(){
    cout << "Hello, world!\n";
}

//  If we write the function in the bottom( after main() function ) then the program will throw an error
//  like this --> 'sum' was not declared in this scope.
//  We can simply write function prototype for getting out of this errors.
//  Also Function Prototypes are good practise.