#include <stdio.h>
#include <stdlib.h>
int main(){
    int n;
    int *ptr;
    scanf("%d", &n);
    // int arr[n]; // NOT ALLOWED IN C LANGUAGE!
    ptr = (int*) malloc(n * sizeof(int));
    ptr[0] = 31;
    ptr[1] = 37;
    ptr[2] = 89;
    printf("%d %d %d", ptr[0], ptr[1], ptr[2]);
    return 0;
}