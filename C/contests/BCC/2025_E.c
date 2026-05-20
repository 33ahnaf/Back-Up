#include <stdio.h>

int isPrime(int i);

int main(){
    int N;
    scanf("%d", &N);
    isPrime(N) ? printf("Yes\n") : printf("No\n");
    return 0;
}

int isPrime(int N){
    int isIsPrime = 1;
    if(N == 0 || N == 1) return 0;
    if(N == 2) return 1;
    for (int i = 2; i < N; i++){
        if(N % i == 0){ isIsPrime = 0; break; }
    }
    return isIsPrime;
}