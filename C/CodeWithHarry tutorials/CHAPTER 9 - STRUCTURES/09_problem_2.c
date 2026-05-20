#include <stdio.h>
typedef struct vector
{
    int i;
    int j;
}vec;
struct vector SumVector(struct vector v1, struct vector v2);
struct vector SumVector(struct vector v1, struct vector v2){
    struct vector v3 = {v1.i + v2.i, v1.j + v2.j};
    return v3;
}

int main(){
    vec v1 = {5, 4};
    vec v2 = {4, 8};
    vec v3 = SumVector(v1, v2);
    printf("Sum of vectors is: %d i + %d j", v3.i, v3.j);
    return 0;
}