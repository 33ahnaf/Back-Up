#include <iostream>

using namespace std;

int factorial(int n){
    if (n <= 1)
    {
        return 1;
    }
    return n * factorial(n-1);
}

    // This functions are called "Recursive Function". ("Recursions" happens in "Recursive Function")

int fibonacci(int n){
    if(n < 2)
    {
        return n;
    }
    return fibonacci(n-2) + fibonacci(n-1);
}

int main(){
    // Factorial of a number:
    // 6! = 6*5*4*3*2*1 = 720
    // 0! = 1 by definition
    // 1! = 1 by definition
    // n! = n * (n-1)!

    // 6! = 6 * (5)!
    // 5! = 5 * (4)!
    // 4! = 4 * (3)!
    // 3! = 3 * (2)!
    // 2! = 2 * (1)!
    // 1! = 1

    int num;
    cout << "Enter a number: ";
    cin >> num;
    int factorial_of_num = factorial(num);
    cout << "The Factorial of " << num << " is: " << factorial_of_num;



    // Fibonacci of a number:
    // Fibonacci(n) = Fibonacci(n-2) + Fibonacci(n-1)

    int num;
    cout << "Enter a number: ";
    cin >> num;
    int fibonacci_of_num = fibonacci(num);
    cout << "The value at term " << num << " of fibonacci series is: " << fibonacci_of_num;
    return 0;
}