#include <stdio.h>

int isCHAR(char a){
    int result = 0;
    char chars[52] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for(int i = 0; i < 52; i++){
        if(a == chars[i])
            result = 1;
    }
    return result;
}

int isDIGIT(char a){
    int result = 0;
    char chars[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for(int i = 0; i < 10; i++){
        if(a == chars[i])
            result = 1;
    }
    return result;
}

int main(){
    int n;
    char input[50];
    scanf("%d", &n);
    while(n--){
        scanf("%s", input);

        int isRXCY = 0;
        int r_pos = -1;
        int c_pos = -1;
        if(input[0] == 'R' && isDIGIT(input[1])){
            for(int i = 2; input[i] != '\0'; i++){
                if(input[i] == 'C' && isDIGIT(input[i+1])){
                    isRXCY = 1;
                    r_pos = 0;
                    c_pos = i;
                    break;
                }
            }
        }


    }
    return 0;
}