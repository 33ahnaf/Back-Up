#include <stdio.h>
#include <stdlib.h>

int main(){
    int arr_size = 5;
    float *arr;
    arr = (float*) malloc(arr_size * sizeof(float));
    arr[0] = 12.432;
    arr[1] = 212.424;
    arr[2] = 342.12;
    arr[3] = 53.21;
    arr[4] = 57.56;
    printf("%.3f\n", arr[0]);
    printf("%.3f\n", arr[1]);
    printf("%.3f\n", arr[2]);
    printf("%.3f\n", arr[3]);
    printf("%.3f\n", arr[4]);
    return 0;
}