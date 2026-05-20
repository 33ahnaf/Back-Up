#include <stdio.h>

int fibonacci(int);

int fibonacci(int n){
    if (n == 1 || n == 2)
    {
        return n-1;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}

int main(){
    int a = 10;
    int b = fibonacci(a);
    printf("Fibonacci = %d", b);
    return 0;
}