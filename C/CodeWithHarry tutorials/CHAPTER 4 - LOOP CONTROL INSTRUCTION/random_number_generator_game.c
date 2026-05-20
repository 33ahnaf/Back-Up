#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(0));
    int random_num = (rand() % 100) + 1;
    int user_input, number_of_guesses = 0;
    printf("Welcome to random number generator game\n");
    printf("---------------------------------------\n");
    while (1)
    {
        printf("Enter a number:");
        scanf("%d", &user_input);
        if (random_num>user_input)
        {
            number_of_guesses++;
            printf("The number is higher than %d\n", user_input);
        }
        if (random_num<user_input)
        {
            number_of_guesses++;
            printf("The number is lower than %d\n", user_input);
        }
        if (random_num == user_input)
        {
            number_of_guesses++;
            break;
        }
    }
    printf("You gussed it correctly.\n");
    printf("--------------------------\n");
    printf("Number of guesses: %d", number_of_guesses);
    return 0;
}