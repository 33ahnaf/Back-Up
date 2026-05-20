#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void decrypt(char *input){
    for(int i = 0; i < strlen(input); i++) input[i] == '\n' ? (input[i] = input[i]) : (input[i] -= 5);
}

int main(){
    FILE *file;
    file = fopen("data.txt", "r");
    int charLength = 0;
    while(fgetc(file) != EOF) charLength++;
    char *data = (char*) malloc(charLength * sizeof(char));
    data[(sizeof(data) / sizeof(char)) - 1] = '\0';
    rewind(file); // resets the file pointer.
    for(int i = 0; i < charLength; i++) data[i] = fgetc(file);
    decrypt(data);
    printf("%s", data);
    free(data);
    fclose(file);
    return 0;
}
