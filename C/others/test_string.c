#include <stdio.h>

int main(){
    char user_input[26];
    printf("Enter a text: ");
    scanf("%25s", user_input);
    printf("User Input: %s\n", user_input);
    printf("Enter a text: ");
    scanf("%25s", user_input);
    printf("User Input: %s", user_input);
    return 0;
}