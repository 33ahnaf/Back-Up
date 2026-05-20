#include <iostream>

int main(){
    int x = 5;
    int &y = x;
    std::cout << "x = " << x << " y = " << y << "\n";
    x = 7;
    std::cout << "x = " << x << " y = " << y << "\n";
    y = 12;
    std::cout << "x = " << x << " y = " << y << "\n";
    return 0;
}