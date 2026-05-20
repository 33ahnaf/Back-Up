#include <stdio.h>
#include <stdlib.h>

int main(){
    int arr_size;
    int *arr;
    printf("Array size: ");
    scanf("%d" ,&arr_size);
    arr = (int*) calloc(arr_size, sizeof(int));
    arr[0] = 12;
    arr[1] = 23;
    arr[2] = 38;
    printf("%d\n%d\n%d", arr[0], arr[1], arr[2]);
    return 0;
}