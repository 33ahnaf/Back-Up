#include <stdio.h>
#include <stdlib.h>

int main(){
    int arr_size;
    int *arr;
    printf("Array size: ");
    scanf("%d" ,&arr_size);
    arr = (int*) malloc(arr_size * sizeof(int));
    arr[0] = 12;
    arr[1] = 23;
    arr[2] = 38;
    free(arr); // free function release the memory pointer. remember free() function only works with a pointer that previously allocated using malloc() or calloc().
    printf("%d\n%d\n%d", arr[0], arr[1], arr[2]); // thats why this prints garbage value.
    return 0;
}