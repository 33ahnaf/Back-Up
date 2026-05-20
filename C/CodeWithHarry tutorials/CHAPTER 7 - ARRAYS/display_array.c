#include <stdio.h>

int main(){
    int arr[10], x;
    printf("Enter a number:");
    scanf("%d", &x);
    for (int i = 0; i < 10; i++)
    {
        arr[i] = x*(i+1);
    }
    printf("arr = [");
    for (int j = 0; j < 10; j++)
    {
        printf(" %d,", arr[j]);
    }
    printf("]");
    return 0;
}