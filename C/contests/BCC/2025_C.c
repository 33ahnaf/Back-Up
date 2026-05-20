#include <stdio.h>

int check_luck(int i);

int main(){
    int userInput;
    scanf("%d", &userInput);
    if(check_luck(userInput)){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
    return 0;
}

int check_luck(int input){
    int luckyNums[] = {4, 7, 44, 47, 74, 77, 444, 447, 474, 477, 744, 747, 774, 777};
    int isAlmostLucky = 0;
    for(int i = 0; i < sizeof(luckyNums) / sizeof(int); i++){
        if(input % luckyNums[i] == 0){
            isAlmostLucky = 1;
            break;
        }
    }
    return isAlmostLucky;
}