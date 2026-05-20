//  Copyright: ©Ahnaf Shariar 2025
//
//  Code originally wrote 02 January 2025
//  by Md. Ahnaf Shariar
//
//  This example code is in the public domain.

#include <stdio.h>
#include <string.h>
#define max_characters 101


int findIndex(char character_array[], char character){ // Create a function for finding the index of a character. if character not found then it returns -2 (because I add 1 with the output. see below code..)
    for (int i = 0; i < strlen(character_array); i++)
    {
        if (character_array[i] == character)
        {
            return i;
        }
    }
    return -2;
}


int main(){
    char valid_character_capital[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    // Create an array of characters for storing the valid capital letters.
    char valid_character_small[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    // Create an array of characters for storing the valid small letters.
    char binary_values[26][6] = {"00001", "00010", "00011", "00100", "00101", "00110", "00111", "01000", "01001", "01010", "01011", "01100", "01101", "01110", "01111", "10000", "10001", "10010", "10011", "10100", "10101", "10110", "10111", "11000", "11001", "11010"};
    // Create an array of characters for storing the binary values of the characters.
    char user_input_text[max_characters]; // Create a "char" variable to store the text.

    printf("Enter: ");
    fgets(user_input_text, max_characters, stdin); // input the text from user.


    for (int i = 0; i < (strlen(user_input_text)-1); i++) // loop thorugh all the characters of the user_input_text
    {

        if (user_input_text[i] != ' ' && ((findIndex(valid_character_capital, user_input_text[i])+1) != -1 || (findIndex(valid_character_small, user_input_text[i])+1) != -1)) // checks that if user_input_text[i] is not " "(space) and the character exists in valid_character_small or in valid_character_capital.
        {

            if ((findIndex(valid_character_capital, user_input_text[i])+1) != -1) // checks if the character exists in valid_character_capital.
            {
                printf("%c (%d) -> %s\n", user_input_text[i], findIndex(valid_character_capital, user_input_text[i])+1, binary_values[findIndex(valid_character_capital, user_input_text[i])]); // first, prints the character then prints the character's serial No then prints the binary value of the character.
            }
            else if ((findIndex(valid_character_small, user_input_text[i])+1) != -1) // checks if the character exists in valid_character_small.
            {
                printf("%c (%d) -> %s\n", user_input_text[i], findIndex(valid_character_small, user_input_text[i])+1, binary_values[findIndex(valid_character_small, user_input_text[i])]); // first, prints the character then prints the character's serial No then prints the binary value of the character.
            }

        }else if (user_input_text[i] == ' ') // checks whether the character is " "(space) or not.
        {
            printf("\n"); // if " "(space) then prints "\n"
        }else{ // checks whether the character is ( " "(space) or valid character ) or not.
            printf("Invalid character. . . !\t-> %c\n", user_input_text[i]); // if the character is not valid then prints "Invalid character. . . !" and then prints the character.
        }

    }
    char exit_character;
    printf("\nPress enter to exit > ");
    scanf("%c", &exit_character);
    return 0;
} // That's it. (it took me only about 3-4 hours  :)