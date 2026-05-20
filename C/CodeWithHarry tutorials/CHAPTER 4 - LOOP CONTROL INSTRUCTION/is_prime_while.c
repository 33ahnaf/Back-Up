#include <stdio.h>

int main(){
    int prime, i;
    int result;
    printf("Enter a number:\n");
    scanf("%d", &prime);
    if (prime == 2)
    {
        result = 1;
    }
    else
    {
        i = 2;
        while (i<prime)
        {
            if (prime%i != 0)
        {
            result = 1;
        }
        else
        {
            result = 0;
            break;
        }
        i++;
        }
        
    }
    
    if (result == 1)
    {
        printf("This is a prime number.\n");
    }
    else
    {
        printf("This is not a prime number.\n");
    }
    
    return 0;
}