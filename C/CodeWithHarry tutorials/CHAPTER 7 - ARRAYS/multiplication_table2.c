#include <stdio.h>

int main(){
    int user_number, multiplication_table[10];
    printf("Enter a number:");
    scanf("%d", &user_number);
    for (int i = 0; i < 10; i++)
    {
        multiplication_table[i] = user_number*(i+1);
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d X %d = %d\n", user_number, i+1, multiplication_table[i]);
    }
    return 0;
}