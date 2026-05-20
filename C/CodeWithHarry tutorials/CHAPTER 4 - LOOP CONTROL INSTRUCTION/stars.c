#include <stdio.h>

int main()
{
    int user_input;
    int x;
    int i;
    printf("Enter a number:\n");
    scanf("%d", &user_input);
    for (i = 0; i < user_input; i++)
    {
        for (x = 0; x < 2 * i + 1; x++)
        {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}