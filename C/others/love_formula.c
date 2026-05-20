#include <stdio.h>

#define MAX_LENGTH 33

int lengthOfString(const char *);
void assignStr(char *, char *);





int main(int argc, char **argv){
    char male[MAX_LENGTH], female[MAX_LENGTH];
    int elements[MAX_LENGTH];

    if(argc == 3){
        assignStr(argv[1], male);
        assignStr(argv[2], female);
    }else{
        printf("Name of the male: ");
        scanf("%s", male);
        printf("Name of the female: ");
        scanf("%s", female);
    }

    for(int i = 0; i < lengthOfString(male); i++){
        for(int j = 0; j < lengthOfString(female); j++){
            if(male[i] == female[j] && male[i] != '~'){
                male[i] = '~';
                female[j] = '~';
                elements[i] = 2;
                break;
            }
        }
    }
    printf("%d\n", TWOsCount);
    return 0;
}





int lengthOfString(const char *str){
    int i = 0;
    for(; str[i] != '\0' && str[i] != '\n'; i++);
    return i;
}

void assignStr(char *input, char *AssigningTo){
    for(int i = 0; i < lengthOfString(input); i++){
        AssigningTo[i] = input[i];
    }
}
