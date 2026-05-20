#include <stdio.h>

int main(){
    int i, x, sum;
    printf("Enter value:\n");
    scanf("%d", &x);
    for ( i = 1; i <= 10; i++)
    {
        sum+=x*i;
    }
    printf("The sum is %d\n", sum);
    return 0;
}