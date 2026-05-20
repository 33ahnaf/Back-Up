#include <stdio.h>

int factorial(int input);

int main(){
    int T;
    int Nums[20];
    scanf("%d", &T);
    for(int i = 0; i < T; i++){
        scanf("%d", &Nums[i]);
    }
    for(int i = 0; i < T; i++){
        printf("%d\n", factorial(Nums[i]));
    }
    return 0;
}

int factorial(int input){
    if(input == 0 || input == 1) return 1;
    return input * factorial(input - 1);
}