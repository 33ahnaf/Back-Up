#include <stdio.h>

int main(){
    char name[31];
    printf("Enter your name: ");
    gets(name); // gets() function is used to input a multi-line string.
    printf("Your name: %s", name);

    return 0;
}