#include <stdio.h>
#include <string.h>

void remove_newline(char *input){
    if (strlen(input) > 0 && input[strlen(input) - 1] == '\n'){
        input[strlen(input) - 1] = '\0';
    }
}

int main(){
    char name[31];
    printf("Enter: ");
    fgets(name, sizeof(name), stdin);

    remove_newline(name);

    printf("Name: %s\n", name);
    printf("Name: %s", name);
    printf("Hello!");
    return 0;
}