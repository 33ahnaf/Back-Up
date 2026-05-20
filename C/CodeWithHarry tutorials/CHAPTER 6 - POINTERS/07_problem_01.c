#include <stdio.h>

int main(){
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* ptr = nums;
    printf("The value at address %u is %d\n", (ptr+3), *(ptr+3));
    return 0;
}