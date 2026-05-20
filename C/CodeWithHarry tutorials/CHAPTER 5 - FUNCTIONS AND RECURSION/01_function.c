#include <stdio.h>
int sum(int, int);
int sum(int x, int y){
    return x+y;
}
int main(){
    int a, b, c;
    a = sum(5, 7);
    b = sum(13, 6);
    c = sum(8, 7);
    printf("Sum = %d\n", a);
    printf("Sum = %d\n", b);
    printf("Sum = %d\n", c);
    return 0;
}