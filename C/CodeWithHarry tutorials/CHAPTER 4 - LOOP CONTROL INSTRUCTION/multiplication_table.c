#include <stdio.h>

int main(){
    int i, x;
    printf("Enter value:\n");
    scanf("%d", &x);
    for ( i = 1; i <= 10; i++)
    {
        printf("%d X %d = %d\n", x, i, x*i);
    }
    
    return 0;
}