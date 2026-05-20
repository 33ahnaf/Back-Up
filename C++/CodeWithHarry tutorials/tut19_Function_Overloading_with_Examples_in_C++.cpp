#include <iostream>

using namespace std;

int sum(int a, int b){
    return a+b;
}

int sum(int a, int b, int c){
    return a+b+c;
}

// Calculate the area of a cube.
int volume(int a){
    return (a * a * a);
}

// Calculate the area of a cylinder.
float volume(int r, int h){
    return (3.1415 * r * r * h);
}

int main(){
    int a = 5, b = 7, c = 10;
    cout << "The sum of " << a << " and " << b << " is: " << sum(a, b) << "\n";
    cout << "The sum of " << a << ", " << b << " and " << c << " is: " << sum(a, b, c) << "\n\n";
    // We can create two slightly different functions and they will not throw an error.
    int r = 5, h = 10, a = 5;
    cout << "The volume of a cube which has a length of " << a << " cm is: " << volume(a) << " cubic cm" << "\n";
    cout << "The volume of a cylinder which has a radius of " << r << " cm and hight of " << h << " cm is: " << volume(r, h) << " cubic cm" << "\n";
    return 0;
}