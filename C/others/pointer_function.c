#include <stdio.h>

void *square(int *x);
void *square(int *x){
    *x = (*x)*(*x)*(*x);
}

int main(){
    int a = 3;
    printf("a = %d\n", a);
    square(&a);
    printf("a^3 = %d", a);
    return 0;
}