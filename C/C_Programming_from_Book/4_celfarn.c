#include <stdio.h>
#include <stdlib.h>

void main(){
    float farn, cel;
    system("clear");

    printf("\n Enter temperature in centigrade: ");
    scanf("%f", &cel);

    farn = 1.8 * cel + 32;

    printf("\n Fahrenheit equivalent is : %.2f\n\n", farn);
    getchar();
}
