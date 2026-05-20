#include <stdio.h>

int main(){
    char name[26]; // Why 26, right? I set it to 26 so it can hold strings up to 25 charecter.
    printf("Enter your name: ");
    scanf("%25s", name); // I set it to %25s so the max size of the input string will be no more than 25.
    printf("Your name: %s\n", name); // :)

    return 0;
}