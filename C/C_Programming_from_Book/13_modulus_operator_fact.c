#include <stdio.h>
#include <stdlib.h>

int main(){
    int a = 10, b = 3;
    printf(" +%d mod +%d = %d\n", a, b, a%b);
    printf(" +%d mod -%d = %d\n", a, b, a%(-b));
    printf(" -%d mod +%d = %d\n", a, b, (-a)%b);
    printf(" -%d mod -%d = %d\n", a, b, (-a)%(-b)); 
    return 0;
}
