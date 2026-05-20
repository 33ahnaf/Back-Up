#include <iostream>

using namespace std;

class employee{
    private:
        int a, b, c;
    public:
        int d, e;
        void setData(int a1, int b1, int c1); // Function declaration.
        void getData(){
            cout << "The value of a is: " << a << "\n";
            cout << "The value of b is: " << b << "\n";
            cout << "The value of c is: " << c << "\n";
            cout << "The value of d is: " << d << "\n";
            cout << "The value of e is: " << e << "\n";
        }
};

void employee :: setData(int a1, int b1, int c1){
    a = a1;
    b = b1;
    c = c1;
}

int main(){
    employee ahnaf;
    ahnaf.d = 37;
    ahnaf.e = 49;
    ahnaf.setData(23, 34, 99);
    ahnaf.getData();
    return 0;
}