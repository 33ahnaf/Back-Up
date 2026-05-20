#include <iostream>

using namespace std;

void print2int(int a, int b){
    cout << "The value of 1st variable is: " << a << "\n";
    cout << "The value of 2nd variable is: " << b << "\n";
}

int main(){
    int x = 5, y = 7;
    print2int(x, y);
    return 0;
}