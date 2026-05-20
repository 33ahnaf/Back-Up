#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_SIZE 50

void main(){
    char ch, name[MAX_SIZE];
    int i;

    system("clear");
    printf("Hello! please type your name: ");

    for(int i = 0; (ch = getchar()) != '\n'; i++){
        name[i] = ch;
    }

    printf("\n %s %s%s", "Nice to meet you", name, ".");
    usleep(1000 * 1000);

    printf("\n Your name spelled backward is: ");
    for(; i >= 0; i--){
        putchar(name[i]);
    }
    printf("\n\n\n Have a nice day. . . .\a\a\a\n");
    usleep(5000 * 1000);
}
