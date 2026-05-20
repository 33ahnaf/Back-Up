#include <stdio.h>
struct vector
{
    int i;
    int j;
};

int main(){
    struct vector v = {1, 2};
    printf("The value of vector is: %d i + %d j", v.i, v.j);
    return 0;
}