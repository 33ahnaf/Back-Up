#include <stdio.h>
#include <string.h>

#define MAX_CHAR 101

void removeNewline(char *input){
    if(strlen(input) > 0 && input[strlen(input) - 1] == '\n'){
        input[strlen(input) - 1] = '\0';
    }
}

int findIndex(char array[], char target){
    for(int i = 0; i < strlen(array); i++){
        if(array[i] == target) return i;
    }
    return -1;
}

int main(){
    char userInput[MAX_CHAR];
    char morseCodeValues[26][5] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    char smallLetters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char capitalLetters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    
	while(1){
		printf(">");
		fgets(userInput, MAX_CHAR, stdin);
		removeNewline(userInput);

		for(int i = 0; i < strlen(userInput); i++){
			if(findIndex(smallLetters, userInput[i]) != -1){
				printf("%s ", morseCodeValues[findIndex(smallLetters, userInput[i])]);
			}else if(findIndex(capitalLetters, userInput[i]) != -1){
				printf("%s ", morseCodeValues[findIndex(capitalLetters, userInput[i])]);
			}else{
				switch(userInput[i]){
					case ' ':
						printf("/ ");
						break;
					case '.':
						printf(".-.-.- ");
						break;
					case ',':
						printf("--..-- ");
						break;
					case '\'':
						printf(".----.");
						break;
					case '?':
						printf("..--..");
						break;
					case '!':
						printf("-.-.--");
						break;
					default:
						printf("# ");
				}
			}
		}
		printf("\n");
	}
    return 0;
}
// It took me only 38 minutes.
