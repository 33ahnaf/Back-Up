#include <stdio.h>
#include <string.h>

#define MAX_CHAR_LIMIT 100

void removeNewine(char *array){
    if(strlen(array) > 0 && array[strlen(array) - 1] == '\n') array[strlen(array) - 1] = '\0';
}

int main(){
    char user_input[MAX_CHAR_LIMIT];
    while(1){
        printf(">>");
        fgets(user_input, sizeof(user_input), stdin);
        removeNewine(user_input);
        if(!strcasecmp(user_input, "echo")){
            printf(">>>");
            fgets(user_input, sizeof(user_input), stdin);
            removeNewine(user_input);
            printf("%s\n", user_input);
        }else if(!strcasecmp(user_input, "exit")){
            return 0;
        }else{
            if(!strcasecmp(user_input, "")){
                continue;
            }
            printf("\'%s\' is not defined.\n", user_input);
        }
    }
    return 0;
}