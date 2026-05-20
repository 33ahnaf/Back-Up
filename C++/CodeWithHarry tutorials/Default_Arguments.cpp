#include <iostream>

using namespace std;

int add_100_or_more(int num, int adder = 100){ // adder = 100 is a default argument
    return num + adder;
}

int main(){
    int num;
    cout << "Enter a number: ";
    cin >> num;
    cout << "Adder = default: " << add_100_or_more(num) << "\n";
    cout << "Adder = 205: " << add_100_or_more(num, 205) << "\n";
    return 0;
}