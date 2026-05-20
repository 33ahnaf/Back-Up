#include <iostream>

using namespace std;

int c = 45;

int main(){
    // ********** Calling Local and Global Variables **********
    int a, b, c;
    cout<<"Enter the value of a: ";
    cin>>a;
    cout<<"Enter the value of b: ";
    cin>>b;
    c = a+b;
    cout<<"The sum is: "<<c<<"\n";
    cout<<"The value of global c is: "<<::c<<"\n"; // :: <-- This thing is called Scope Resolution Operator and it gives global c value.

    //********** Difference between float, double and long double **********
    float d = 34.4f; // why the f you ask? well.. if we pass a float value like this cout<<34.4; then it will consider 34.4 as a double not float, thats why we have to cout<<34.4f; if we want to pass a float value. And in this line float d = 34.4f the f is not nececerry because we called it float at the first, but writing f is a good practice.
    long double e = 34.4l; // And l for long double. // Remember double and long double are different.
    cout<<"The size of 34.4 is: "<<sizeof(34.4)<<"\n";
    cout<<"The size of 34.4 is: "<<sizeof(34.4f)<<"\n";
    cout<<"The size of 34.4 is: "<<sizeof(34.4F)<<"\n";
    cout<<"The size of 34.4 is: "<<sizeof(34.4l)<<"\n";
    cout<<"The size of 34.4 is: "<<sizeof(34.4L)<<"\n";

    //********** Reference Variables **********
    int x = 420;
    int y = x;
    cout<<"x = "<<x<<" y = "<<y<<"\n";
    x = 430;
    cout<<"x = "<<x<<" y = "<<y; // In this code block, changing x does not change y (but the bottom one does).
    
    int x = 420;
    int & y = x;
    cout<<"x = "<<x<<" y = "<<y<<"\n";
    x = 430;
    cout<<"x = "<<x<<" y = "<<y; // In this code block, changing x does change y.

    //********** Typecasting **********
    int a = 45;
    float b = 45.46;
    cout<<(int)a<<"\n";
    cout<<int(a)<<"\n"; // Same as the upper one.

    cout<<(float)a<<"\n";
    cout<<float(a)<<"\n"; // Same as the upper one.

    cout<<(float)b<<"\n";
    cout<<float(b)<<"\n"; // Same as the upper one.

    cout<<(int)b<<"\n";
    cout<<int(b)<<"\n"; // Same as the upper one.

    int c = int(b); // This is valid.
    int c = (int)b; // This is also valid.

    cout<<a + b<<"\n"; // This will output 90.46
    cout<<a + (int)b<<"\n"; // This will output 90
    cout<<a + int(b)<<"\n"; // This will output 90
    
    // Please run only one subject at a time.
    return 0;
}