#include <stdio.h>
#include <string.h>

#define MAX_CHAR 201

void removeNewline(char *array){
    if(strlen(array) > 0 && array[strlen(array) - 1] == '\n') array[strlen(array) - 1] = '\0';
}

void encrypt(char *input){
    for(int i = 0; i < strlen(input); i++) input[i] == '\n' ? (input[i] = input[i]) : (input[i] += 5);
}

int main(){
    FILE *data_File;
    data_File = fopen("data.txt", "a");
    char userInput[MAX_CHAR];
    while(1){
        printf("Enter >");
        fgets(userInput, MAX_CHAR, stdin);
        removeNewline(userInput);
        if(!strcasecmp(userInput, "exit")) break;
        encrypt(userInput);
        printf("%s\n", userInput);
        fprintf(data_File, "%s\n", userInput);
    }
    fclose(data_File);
    return 0;
}
