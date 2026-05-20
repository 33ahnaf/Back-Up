#include <iostream>

using namespace std;

int main(){
    // What is a pointer? --> Pointer is a data type which holds the address of other data types.
    int a = 3;
    int *ptr;
    ptr = &a; // same as --> int *ptr = &a;

    // & --> Address of operator (Address of)
    cout << "Address of a is(using ptr): " << ptr << "\n";
    cout << "Address of a is(using &a):  " << &a << "\n";

    // * --> Dereference operator (Value at)
    cout << "Value at address of a is(using *ptr):  " << *ptr << "\n";
    cout << "Value at address of a is(using *(&a)): " << *(&a) << "\n";

    cout << "\n";

    // Pointer to pointer
    int **ptr2 = &ptr;
    cout << "Address of ptr is: " << ptr2 << "\n";
    cout << "Value at address of ptr is: " << *ptr2 << "\n";
    cout << "Value at address of value at value at ptr2 is: " << **ptr2 << "\n";

    return 0;
}