#include <stdio.h>

int main(){
    int x = 1971;
    int y = 1979;
    int* a = &x;
    printf("The address of x is %u\n", &x);
    printf("The address of x is %p\n", a);
    printf("The address of y is %p\n", &y);
    printf("The value of x is %u\n", *(a));
    return 0;
}