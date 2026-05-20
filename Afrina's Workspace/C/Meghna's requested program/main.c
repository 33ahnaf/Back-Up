// Saturday, March 1, 2025, 5:25:27 PM (UTC +6:00)
// Saturday, March 1, 2025, 7:47:50 PM (UTC +6:00)

//  Copyright: ©Ahnaf Shariar 2025
//
//  Code originally wrote 01 March 2025
//  by Md. Ahnaf Shariar
//
//  This example code is in the public domain.

#include <stdio.h>
#include <string.h>

#define admin_name "Meghna"



void print_something_X_times(char text[], char character_to_print[]) {
    for (int i = 0; i < strlen(text); i++)
    {
        printf("%s", character_to_print);
    }
}

void remove_newline(char *input){
    if (strlen(input) > 0 && input[strlen(input) - 1] == '\n'){
        input[strlen(input) - 1] = '\0';
    }
}

void print_question_with_options(short int question_no, char question[], char option1[], char option2[], char option3[], char option4[]) {
    printf("%d. %s\n\tA. %s\tB. %s\n\tC. %s\tD. %s", question_no, question, option1, option2, option3, option4);
}

void get_answer(char* pointer1) {
    printf("\nEnter: ");
    scanf(" %c", pointer1);
}



int main()
{
    FILE *my_file;
    my_file = fopen("data.txt", "a");
    char username[21];
    char user_input_answer;
    int score = 0;

    printf("How well do you know %s?\n", admin_name);
    printf("----------------------");
    print_something_X_times(admin_name, "-");

    printf("\nEnter username: ");
    fgets(username, sizeof(username), stdin);
    remove_newline(username);

    print_question_with_options(1, "Meghna\'s favourite topic is?", "Coding", "Studying", "Eating", "Drawing");
    get_answer(&user_input_answer);
    if (user_input_answer == 'D' || user_input_answer == 'd'){
        score++;
    }else{
        // do nothing.
    }
    
    print_question_with_options(2, "What would Meghna do if Meghna won a lottery?", "Travel the world", "Invest it", "Shopping", "Buy a sports car");
    get_answer(&user_input_answer);
    if (user_input_answer == 'A' || user_input_answer == 'a'){
        score++;
    }else{
        // do nothing.
    }

    print_question_with_options(3, "What does Meghna drink the most?", "Tea", "Beer", "Milk", "Green Tea");
    get_answer(&user_input_answer);
    if (user_input_answer == 'C' || user_input_answer == 'c'){
        score++;
    }else{
        // do nothing.
    }

    print_question_with_options(4, "Where would Meghna like to go with Meghna's soulmate?", "Paris", "Hawaii", "Venice ", "Bahamas");
    get_answer(&user_input_answer);
    if (user_input_answer == 'D' || user_input_answer == 'd'){
        score++;
    }else{
        // do nothing.
    }

    print_question_with_options(5, "Which superpower would Meghna choose?", "Fly like Superman", "Be invisible", "See Ghosts ", "Read Minds of the people");
    get_answer(&user_input_answer);
    if (user_input_answer == 'D' || user_input_answer == 'd'){
        score++;
    }else{
        // do nothing.
    }

    print_question_with_options(6, "Which animal does Meghna dream to pet?", "A Dog", "A Rabbit", "A Cat", "A Hamster");
    get_answer(&user_input_answer);
    if (user_input_answer == 'C' || user_input_answer == 'c'){
        score++;
    }else{
        // do nothing.
    }

    print_question_with_options(7, "With whom would Meghna like to spend some quality time?", "Elon Musk", "Travis Scott", "YOU", "Christopher Nolan");
    get_answer(&user_input_answer);
    if (user_input_answer == 'C' || user_input_answer == 'c'){
        score++;
    }else{
        // do nothing.
    }

    print_question_with_options(8, "What type of movies does Meghna like?", "Romance", "Action", "Thriller", "Comedy");
    get_answer(&user_input_answer);
    if (user_input_answer == 'D' || user_input_answer == 'd'){
        score++;
    }else{
        // do nothing.
    }

    print_question_with_options(9, "In Meghna's freetime where would Meghna like to go?", "Gym", "Sleeping", "Shopping", "Library");
    get_answer(&user_input_answer);
    if (user_input_answer == 'B' || user_input_answer == 'b'){
        score++;
    }else{
        // do nothing.
    }

    print_question_with_options(10, "Meghna's favourite TV series is", "Game of Thrones", "Breaking Bad", "FRIENDS", "Hidden Love");
    get_answer(&user_input_answer);
    if (user_input_answer == 'D' || user_input_answer == 'd'){
        score++;
    }else{
        // do nothing.
    }

    printf("--------------\n");
    printf("Your score: %d\n", score);
    printf(">> More info in data.txt <<\n");

    fprintf(my_file, "%s\t-\t%d\n", username, score);
    fclose(my_file);
    printf("Press Enter to exit >");
    scanf(" %c");
    return 0;
}
// That's it. 2 hours and 22 minutes have been passed :)