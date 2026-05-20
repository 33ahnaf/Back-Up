#include <iostream>

int b = 87; // This is a global variable because it is created in the top of the code(not in any function like for loop, main() etc.).

using namespace std;

int main(){
    int a = 34; // This is a local variable because it is created in a function( int main() ).
    float pi = 3.1415;
    char ch = 'A';
    bool bl = true;
    cout<<"a = "<<a<<"\nb = "<<b<<"\npi = "<<pi<<"\nch = "<<ch<<"\nbl = "<<bl;
    return 0;
}