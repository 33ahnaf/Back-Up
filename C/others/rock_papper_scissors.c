#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){

    /*
        0 --> Rock
        1 --> Paper
        2 --> Scissors
    */

    int player, computer;
    srand(time(0));
    computer = rand() % 3;
    
    printf("\nWelcome to rock, paper, scissors game\n");
    printf("-------------------------------------\n");
    printf("0 --> Rock\n1 --> Paper\n2 --> Scissors\n");
    printf("Enter 0 or 1 or 2 to start the game: ");
    scanf("%d", &player);

    if (player == 0 && computer == 0){
        printf("You chose: Rock\t");
        printf("Computer chose: Rock\n");
        printf("-----------------------------------------------\n");
        printf("It's a draw!\n");
    }else if (player == 0 && computer == 1){
        printf("You chose: Rock\t");
        printf("Computer chose: Paper\n");
        printf("-----------------------------------------------\n");
        printf("You lose!\n");
    }else if (player == 0 && computer == 2){
        printf("You chose: Rock\t");
        printf("Computer chose: Scissors\n");
        printf("-----------------------------------------------\n");
        printf("You won!\n");
    }else if (player == 1 && computer == 0){
        printf("You chose: Paper\t");
        printf("Computer chose: Rock\n");
        printf("-----------------------------------------------\n");
        printf("You won!\n");
    }else if (player == 1 && computer == 1){
        printf("You chose: Paper\t");
        printf("Computer chose: Paper\n");
        printf("-----------------------------------------------\n");
        printf("It's a draw!\n");
    }else if (player == 1 && computer == 2){
        printf("You chose: Paper\t");
        printf("Computer chose: Scissors\n");
        printf("-----------------------------------------------\n");
        printf("You lose!\n");
    }else if (player == 2 && computer == 0){
        printf("You chose: Scissors\t");
        printf("Computer chose: Rock\n");
        printf("-----------------------------------------------\n");
        printf("You lose!\n");
    }else if (player == 2 && computer == 1){
        printf("You chose: Scissors\t");
        printf("Computer chose: Paper\n");
        printf("-----------------------------------------------\n");
        printf("You won!\n");
    }else if (player == 2 && computer == 2){
        printf("You chose: Scissors\t");
        printf("Computer chose: Scissors\n");
        printf("-----------------------------------------------\n");
        printf("It's a draw!\n");
    }else {
        printf("Something went Wrong!");
    }
    
    return 0;
}