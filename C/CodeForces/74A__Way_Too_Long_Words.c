#include <stdio.h>
#include <string.h>

int main(){
    char input[101];
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%s", input[i]);
    }
    for(int i = 0; i < n; i++){
        if(strlen(input[i]) > 10){
            printf("%c%d%c", input[i][0], strlen(input[i]) - 2, input[i][strlen(input[i]) - 1]);
        }else{
            printf("%s", input[i]);
        }
        printf("\n");
    }
    return 0;
}