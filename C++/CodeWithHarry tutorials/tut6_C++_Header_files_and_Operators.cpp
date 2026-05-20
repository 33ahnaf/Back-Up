// There are two types of header files:
// 1.System header files: It comes with the compiler.
#include <iostream>
// 2.User defined header files: It is written by the programmer.
// #include "test1.h"
// #include "test1.h" --> This will produce an error if the header file is not present in current directory.

using namespace std;

int main(){
    int a = 4, b = 5;
    cout<<"Hello, world!";
    cout<<"Hello, world!"; // This will output  Hello, world!Hello, world!
    cout<<"Hello, world!"<<endl;
    cout<<"Hello, world!"; // but this will output Hello, world!
    //                                             Hello, world!
    // endl is just like \n but:
    //     endl:
    // Inserts a newline and flushes the output buffer.
    // Flushing means it immediately writes all buffered output to the console, ensuring the output appears at that moment.
    // This is useful if you need to ensure the output is displayed right away (e.g., in debugging).
    // However, excessive use of endl can slow down the program because flushing is more resource-intensive.
    // \n:
    // Inserts a newline without flushing the output buffer.
    // It’s faster than endl because it doesn’t force a flush after each newline, which is ideal for performance, 
    // especially in loops or where flushing isn’t necessary.
    // The actual output appears only when the buffer is flushed (which happens automatically at program end or when needed).
    //
    // soo... \n is just best

    // Arithmetic operators:
    cout<<"\nThese are Arithmetic operators:\n";
    cout<<"a + b = "<<a+b<<endl;
    cout<<"a - b = "<<a-b<<endl;
    cout<<"a * b = "<<a*b<<endl;
    cout<<"a / b = "<<a/b<<endl;
    cout<<"a % b = "<<a%b<<endl;
    cout<<"a++ = "<<a++<<endl;
    cout<<"a-- = "<<a--<<endl;
    cout<<"++a = "<<++a<<endl;
    cout<<"--a = "<<--a<<endl;

    // Assignment operators:
    // int x = 12;
    // float fl = 3.1415;
    // char ch = 'A';

    // Comparison operators:
    cout<<"These are Comparison operators:\n";
    cout<<"a == b: "<<(a==b)<<"\n"; // Brackets is neccecery in c++ but not in c. You can do it in c without brackets.
    cout<<"a != b: "<<(a!=b)<<"\n";
    cout<<"a > b: "<<(a>b)<<"\n";
    cout<<"a < b: "<<(a<b)<<"\n";
    cout<<"a >= b: "<<(a>=b)<<"\n";
    cout<<"a <= b: "<<(a<=b)<<"\n";

    // Logical operators:
    cout<<"These are Logical operators:\n";
    cout<<"OR:\n";
    cout<<"0 || 0: "<<(0 || 0)<<"\n";
    cout<<"0 || 1: "<<(0 || 1)<<"\n";
    cout<<"1 || 0: "<<(1 || 0)<<"\n";
    cout<<"1 || 1: "<<(1 || 1)<<"\n";
    cout<<"AND:\n";
    cout<<"0 && 0: "<<(0 && 0)<<"\n";
    cout<<"0 && 1: "<<(0 && 1)<<"\n";
    cout<<"1 && 0: "<<(1 && 0)<<"\n";
    cout<<"1 && 1: "<<(1 && 1)<<"\n";
    cout<<"NOT:\n";
    cout<<"!0: "<<(!0)<<"\n";
    cout<<"!1: "<<(!1)<<"\n";
    cout<<"NOR:\n";
    cout<<"!(0 || 0): "<<(!(0 || 0))<<"\n";
    cout<<"!(0 || 1): "<<(!(0 || 1))<<"\n";
    cout<<"!(1 || 0): "<<(!(1 || 0))<<"\n";
    cout<<"!(1 || 1): "<<(!(1 || 1))<<"\n";
    cout<<"NAND:\n";
    cout<<"!(0 && 0): "<<(!(0 && 0))<<"\n";
    cout<<"!(0 && 1): "<<(!(0 && 1))<<"\n";
    cout<<"!(1 && 0): "<<(!(1 && 0))<<"\n";
    cout<<"!(1 && 1): "<<(!(1 && 1))<<"\n";
    cout<<"XOR:\n";
    cout<<"!0 && 0 || 0 && !0: "<<((!0 && 0) || (0 && !0))<<"\n"; // According to the formula: !A && B || A && !B = A ⊕ B
    cout<<"!0 && 1 || 0 && !1: "<<((!0 && 1) || (0 && !1))<<"\n"; // According to the formula: !A && B || A && !B = A ⊕ B
    cout<<"!1 && 0 || 1 && !0: "<<((!1 && 0) || (1 && !0))<<"\n"; // According to the formula: !A && B || A && !B = A ⊕ B
    cout<<"!1 && 1 || 1 && !1: "<<((!1 && 1) || (1 && !1))<<"\n"; // According to the formula: !A && B || A && !B = A ⊕ B
    cout<<"XNOR:\n";
    cout<<"!0 && 0 || 0 && !0: "<<(!((!0 && 0) || (0 && !0)))<<"\n"; // According to the formula: !(!A && B || A && !B) = !(A ⊕ B)
    cout<<"!0 && 1 || 0 && !1: "<<(!((!0 && 1) || (0 && !1)))<<"\n"; // According to the formula: !(!A && B || A && !B) = !(A ⊕ B)
    cout<<"!1 && 0 || 1 && !0: "<<(!((!1 && 0) || (1 && !0)))<<"\n"; // According to the formula: !(!A && B || A && !B) = !(A ⊕ B)
    cout<<"!1 && 1 || 1 && !1: "<<(!((!1 && 1) || (1 && !1)))<<"\n"; // According to the formula: !(!A && B || A && !B) = !(A ⊕ B)
    return 0;
}