#include <stdio.h>
typedef struct complex
{
    int real;
    int imaginary;
}complex;
void show(complex c);
void show(complex c){
    printf("Real: %d, Imaginary: %d\n", c.real, c.imaginary);
}
int main(){
    complex c[5];
    for (int i = 0; i < 5; i++)
    {
        printf("Number %d Real: ", i+1);
        scanf("%d", &c[i].real);
        printf("Number %d Imaginary: ", i+1);
        scanf("%d", &c[i].imaginary);
    }
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Number %d ", i+1);
        show(c[i]);
    }
    return 0;
}