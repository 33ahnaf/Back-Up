#include <stdio.h>

int main(){
    int i = 0;
    int sum;
    int x;
    printf("Enter value:\n");
    scanf("%d", &x);
    while (i<x)
    {
        i++;
        sum+=i;
    }
    printf("The sum is %d\n", sum);
    return 0;
}