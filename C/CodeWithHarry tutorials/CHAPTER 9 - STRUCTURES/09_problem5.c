#include <stdio.h>
typedef struct complex
{
    int real;
    int imaginary;
}complex;

int main(){
    complex c1 = {3, 7};
    printf("Real: %d, Imaginary: %d", c1.real, c1.imaginary);
    return 0;
}