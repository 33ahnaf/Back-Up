#include <stdio.h>
#include <stdlib.h>

int main(){
    int n = 6;
    int *arr;
    arr = (int*) calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    return 0;
}