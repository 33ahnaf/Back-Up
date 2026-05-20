#include <stdio.h>
#include <stdlib.h>

int main(){
    int table_of = 7;
    int up_to = 10;
    int *arr = (int*) malloc(up_to * sizeof(int));
    for (int i = 0; i < up_to; i++)
    {
        arr[i] = table_of * (i+1);
    }
    for (int i = 0; i < up_to; i++)
    {
        printf("%d X %d = %d\n", table_of, i+1, arr[i]);
    }
    printf("\n");
    up_to = 15;
    arr = (int*) realloc(arr, up_to * sizeof(int));
    for (int i = 0; i < up_to; i++)
    {
        arr[i] = table_of * (i+1);
    }
    for (int i = 0; i < up_to; i++)
    {
        printf("%d X %d = %d\n", table_of, i+1, arr[i]);
    }

    return 0;
}