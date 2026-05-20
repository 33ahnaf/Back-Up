#include <stdio.h>
#include <stdlib.h>

int main(){
    int pre_size_of_arr = 5;
    int *arr;
    arr = (int*) malloc(pre_size_of_arr * sizeof(int));
    int new_size_of_arr = 10;
    arr = realloc(arr, new_size_of_arr * sizeof(int));
    return 0;
}