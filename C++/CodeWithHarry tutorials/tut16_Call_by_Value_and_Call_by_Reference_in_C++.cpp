#include <iostream>

using namespace std;

int sum(int, int); // Call by Value
int sum(int a, int b)
{
    return a+b; // Return by Value
}

void swap(int *, int *); // Call by Reference (pointer)
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_using_reference_variable(int &, int &); // Call by Reference Variables
void swap_using_reference_variable(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

int & swap_using_reference_variable_int(int &, int &); // Call by Reference Variables
int & swap_using_reference_variable_int(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
    return a; // Function will return a.    // Return by Reference
}

int main(){
    int a1 = 4, b1 = 5;
    cout << "Value = " << sum(a1, b1) << "\n";
    cout << "a = " << a1 << " b = " << b1 << "\n";
    swap(&a1, &b1);
    cout << "a = " << a1 << " b = " << b1 << "\n";

    cout << "\n\n";

    int a2 = 4, b2 = 5;
    cout << "Value = " << sum(a2, b2) << "\n";
    cout << "a = " << a2 << " b = " << b2 << "\n";
    swap_using_reference_variable(a2, b2);
    cout << "a = " << a2 << " b = " << b2 << "\n";
    
    cout << "\n\n";

    int a3 = 4, b3 = 5;
    cout << "Value = " << sum(a3, b3) << "\n";
    cout << "a = " << a3 << " b = " << b3 << "\n";
    swap_using_reference_variable_int(a3, b3) = 48; // The function will return a and a will change value to 48.
    cout << "a = " << a3 << " b = " << b3 << "\n";
    return 0;
}