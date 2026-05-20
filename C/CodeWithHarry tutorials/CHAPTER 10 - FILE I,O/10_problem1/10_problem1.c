#include <stdio.h>

int main(){
    FILE *ptr;
    ptr = fopen("10_problem1.txt", "r");

    // int num;
    // for (int i = 0; i < 3; i++)
    // {
    //     fscanf(ptr, "%d", &num);                                 // We can do this.
    //     printf("%d ", num);
    // }

    // int num1, num2, num3;
    // fscanf(ptr, "%d %d %d", &num1, &num2, &num3);                // We can also do this.
    // printf("The numbers are: %d %d %d", num1, num2, num3);

    fclose(ptr);
    return 0;
}